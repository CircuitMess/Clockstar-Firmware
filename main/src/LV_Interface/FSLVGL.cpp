#include "FSLVGL.h"
#include <cstdio>
#include <dirent.h>
#include <esp_spiffs.h>
#include <esp_log.h>
#include <string>
#include <algorithm>
#include <unordered_map>

static constexpr const char* Cached[] = {
		"/lock_screen/bg.bin",

		"/menu/bg.bin",
		"/menu/batteryFull.bin",
		"/menu/batteryLow.bin",
		"/menu/batteryMid.bin",
		"/menu/phone.bin",
		"/menu/phoneDc.bin",

		"/icon/app_inst.bin",
		"/icon/app_mess.bin",
		"/icon/app_sms.bin",
		"/icon/app_snap.bin",
		"/icon/app_tiktok.bin",
		"/icon/app_wapp.bin",
		"/icon/call_in.bin",
		"/icon/call_miss.bin",
		"/icon/call_out.bin",
		"/icon/cat_email.bin",
		"/icon/cat_entert.bin",
		"/icon/cat_fin.bin",
		"/icon/cat_health.bin",
		"/icon/cat_loc.bin",
		"/icon/cat_news.bin",
		"/icon/cat_other.bin",
		"/icon/cat_sched.bin",
		"/icon/cat_soc.bin",
		"/icon/etc.bin",
		"/icon/lock_closed.bin",
		"/icon/lock_open.bin",
		"/icon/trash.bin",
		"/icon/trash_sel.bin",
		"/icon/back.bin",
		"/icon/back_sel.bin",

		"/clock/0.bin",
		"/clock/1.bin",
		"/clock/2.bin",
		"/clock/3.bin",
		"/clock/4.bin",
		"/clock/5.bin",
		"/clock/6.bin",
		"/clock/7.bin",
		"/clock/8.bin",
		"/clock/9.bin",
		"/clock/colon.bin",
		"/clock/space.bin"

};

static constexpr const char* ThemeDirs[] = {
		"/theme1",
		"/theme2",
		"/theme3",
		"/theme4",
		"/theme5",
		"/theme6",
		"/theme7",
		"/theme8",
		"/theme9"
};

const char* TAG = "FSLVGL";
std::unordered_set<FSLVGL::FileResource, std::hash<RamFile*>> FSLVGL::cache;

FSLVGL::FSLVGL(char letter){
	cache.reserve(sizeof(Cached) / sizeof(Cached[0]) + 16);

	esp_vfs_spiffs_conf_t conf = {
			.base_path = "/spiffs",
			.partition_label = "storage",
			.max_files = 8,
			.format_if_mount_failed = false
	};

	auto ret = esp_vfs_spiffs_register(&conf);
	if(ret != ESP_OK){
		if(ret == ESP_FAIL){
			ESP_LOGE(TAG, "Failed to mount or format filesystem");
		}else if(ret == ESP_ERR_NOT_FOUND){
			ESP_LOGE(TAG, "Failed to find SPIFFS partition");
		}else{
			ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
		}

		return;
	}


	lv_fs_drv_init(&drv);                     /*Basic initialization*/

	drv.letter = letter;                         /*An uppercase letter to identify the drive */
	drv.ready_cb = ready_cb;               /*Callback to tell if the drive is ready to use */
	drv.open_cb = open_cb;                 /*Callback to open a file */
	drv.close_cb = close_cb;               /*Callback to close a file */
	drv.read_cb = read_cb;                 /*Callback to read a file */
	drv.write_cb = write_cb;               /*Callback to write a file */
	drv.seek_cb = seek_cb;                 /*Callback to seek in a file (Move cursor) */
	drv.tell_cb = tell_cb;                 /*Callback to tell the cursor position  */

	drv.dir_open_cb = dir_open_cb;         /*Callback to open directory to read its content */
	drv.dir_read_cb = dir_read_cb;         /*Callback to read a directory's content */
	drv.dir_close_cb = dir_close_cb;       /*Callback to close a directory */

	drv.user_data = this;             /*Any custom data if required*/

	lv_fs_drv_register(&drv);                 /*Finally register the drive*/
}

FSLVGL::~FSLVGL(){
	esp_vfs_spiffs_unregister("storage");
}

auto FSLVGL::findCache(const std::string& lvPath){
	std::string path("/spiffs");
	path.append(lvPath);

	return std::find_if(cache.begin(), cache.end(), [&path](auto fileResource){
		return fileResource.ramFile->path() == path;
	});
}

auto FSLVGL::findCache(void* ptr){
	return std::find_if(cache.begin(), cache.end(), [ptr](auto fileResource){
		return fileResource.ramFile == ptr;
	});
}

void FSLVGL::addToCache(const char* path, bool use32bAligned){
	std::string p;
	if(strchr(path, DriveSeparator) != nullptr){
		p = std::string(path + 2);
	}else{
		p = path;
	}

	auto found = findCache(p);
	if(found != cache.end()){
		found->deleteFlag = false;
		return;
	}

	std::string spath("/spiffs");
	spath.append(p);

	auto ram = new RamFile(spath.c_str(), use32bAligned);
	if(ram->size() == 0){
		delete ram;
		return;
	}

	FileResource r = { ram, false };
	cache.insert(r);
}

void FSLVGL::removeFromCache(const char* path){
	std::string p;
	if(strchr(path, DriveSeparator) != nullptr){
		p = std::string(path + 2);
	}else{
		p = path;
	}

	auto it = findCache(p);
	if(it == cache.end()) return;

	it->deleteFlag = true;
}

void FSLVGL::loadCache(Theme theme){
	std::string themeDir = ThemeDirs[(uint8_t) theme];
	for(const auto& p: Cached){
		std::string filePath = themeDir;
		filePath += p;
		addToCache(filePath.c_str());
	}
}

void FSLVGL::unloadCache(){
	for(auto it = cache.begin(); it != cache.end();){
		if(it->deleteFlag){
			delete it->ramFile;
			it = cache.erase(it);
		}else{
			++it;
		}
	}
}

bool FSLVGL::ready_cb(struct _lv_fs_drv_t* drv){
	return true;
}

void* FSLVGL::open_cb(struct _lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode){
	auto cached = findCache(path);
	if(cached != cache.end()){
		(*cached).ramFile->seek(0);
		return (*cached).ramFile;
	}

	const char* fsMode;

	if(mode == LV_FS_MODE_WR){
		fsMode = "w";
	}else{
		fsMode = "r";
	}

	auto fslvgl = (FSLVGL*) drv->user_data;
	std::string p = fslvgl->Root + std::string(path);

	return (void*) fopen(p.c_str(), fsMode);
}

lv_fs_res_t FSLVGL::close_cb(struct _lv_fs_drv_t* drv, void* file_p){
	auto it = findCache(file_p);
	if(it != cache.end()){
		if(it->deleteFlag){
			delete it->ramFile;
			cache.erase(it);
		}
		return 0;
	}

	fclose((FILE*) file_p);
	return 0;
}

lv_fs_res_t FSLVGL::read_cb(struct _lv_fs_drv_t* drv, void* file_p, void* buf, uint32_t btr, uint32_t* br){
	auto cached = findCache(file_p);
	if(cached != cache.end()){
		*br = (*cached).ramFile->read(buf, btr);
		return 0;
	}

	if(ferror((FILE*) file_p)) return LV_FS_RES_NOT_EX;
	*br = fread(buf, 1, btr, (FILE*) file_p);
	return 0;
}

lv_fs_res_t FSLVGL::write_cb(struct _lv_fs_drv_t* drv, void* file_p, const void* buf, uint32_t btw, uint32_t* bw){
	auto cached = findCache(file_p);
	if(cached != cache.end()){
		*bw = 0;
		return 0;
	}

	if(ferror((FILE*) file_p)) return LV_FS_RES_NOT_EX;

	*bw = fwrite((uint8_t*) buf, 1, btw, (FILE*) file_p);
	return 0;
}

lv_fs_res_t FSLVGL::seek_cb(struct _lv_fs_drv_t* drv, void* file_p, uint32_t pos, lv_fs_whence_t whence){
	auto cached = findCache(file_p);
	if(cached != cache.end()){
		static const std::unordered_map<lv_fs_whence_t, int> SeekMap = {
				{ LV_FS_SEEK_SET, SEEK_SET },
				{ LV_FS_SEEK_CUR, SEEK_CUR },
				{ LV_FS_SEEK_END, SEEK_END },
		};
		(*cached).ramFile->seek(pos, SeekMap.at(whence));
		return 0;
	}

	if(ferror((FILE*) file_p)){
		return LV_FS_RES_NOT_EX;
	}

	int mode;
	switch(whence){
		case LV_FS_SEEK_SET:
			mode = SEEK_SET;
			break;
		case LV_FS_SEEK_CUR:
			mode = SEEK_CUR;
			break;
		case LV_FS_SEEK_END:
			mode = SEEK_END;
			break;
		default:
			mode = SEEK_SET;
	}
	if(fseek((FILE*) file_p, pos, mode) != 0){
		return LV_FS_RES_INV_PARAM;
	}
	return 0;

}

lv_fs_res_t FSLVGL::tell_cb(struct _lv_fs_drv_t* drv, void* file_p, uint32_t* pos_p){
	auto cached = findCache(file_p);
	if(cached != cache.end()){
		*pos_p = (*cached).ramFile->pos();
		return 0;
	}

	if(ferror((FILE*) file_p)) return LV_FS_RES_NOT_EX;
	auto val = ftell((FILE*) file_p);
	if(val == -1) return LV_FS_RES_UNKNOWN;
	*pos_p = val;
	return 0;
}

void* FSLVGL::dir_open_cb(struct _lv_fs_drv_t* drv, const char* path){
	auto fslvgl = (FSLVGL*) drv->user_data;
	std::string p = fslvgl->Root + std::string(path);
	DIR* dir = opendir(p.c_str());
	return dir;

}

lv_fs_res_t FSLVGL::dir_read_cb(struct _lv_fs_drv_t* drv, void* rddir_p, char* fn){
	auto entry = readdir((DIR*) rddir_p);
	if(!entry) return LV_FS_RES_NOT_EX;
	strncpy(fn, entry->d_name, 256);
	return 0;
}

lv_fs_res_t FSLVGL::dir_close_cb(struct _lv_fs_drv_t* drv, void* rddir_p){
	closedir((DIR*) rddir_p);
	return 0;
}

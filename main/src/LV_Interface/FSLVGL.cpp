#include "FSLVGL.h"
#include <cstdio>
#include <dirent.h>
#include <esp_spiffs.h>
#include <esp_log.h>
#include <string>

FSLVGL::FSLVGL(const char* root, char letter) : root(root){

	//init spiffs
	esp_vfs_spiffs_conf_t conf = {
			.base_path = "/spiffs",
			.partition_label = nullptr,
			.max_files = 5,
			.format_if_mount_failed = false
	};
	auto ret = esp_vfs_spiffs_register(&conf);
	const char* TAG = "spiffs";
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

bool FSLVGL::ready_cb(struct _lv_fs_drv_t* drv){
	return true;
}

void* FSLVGL::open_cb(struct _lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode){
	const char* fsMode;

	if(mode == LV_FS_MODE_WR){
		fsMode = "w";
	}else{
		fsMode = "r";
	}

	auto fslvgl = (FSLVGL*) drv->user_data;
	std::string p = std::string(fslvgl->root) + std::string(path);

	return (void*) fopen(p.c_str(), fsMode);
}

lv_fs_res_t FSLVGL::close_cb(struct _lv_fs_drv_t* drv, void* file_p){
	fclose((FILE*) file_p);
	return 0;
}

lv_fs_res_t FSLVGL::read_cb(struct _lv_fs_drv_t* drv, void* file_p, void* buf, uint32_t btr, uint32_t* br){
	if(ferror((FILE*) file_p)) return LV_FS_RES_NOT_EX;
	*br = fread(buf, 1, btr, (FILE*) file_p);
	return 0;
}

lv_fs_res_t FSLVGL::write_cb(struct _lv_fs_drv_t* drv, void* file_p, const void* buf, uint32_t btw, uint32_t* bw){
	if(ferror((FILE*) file_p)) return LV_FS_RES_NOT_EX;

	*bw = fwrite((uint8_t*) buf, 1, btw, (FILE*) file_p);
	return 0;
}

lv_fs_res_t FSLVGL::seek_cb(struct _lv_fs_drv_t* drv, void* file_p, uint32_t pos, lv_fs_whence_t whence){
	if(ferror((FILE*) file_p)) return LV_FS_RES_NOT_EX;

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
	if(!fseek((FILE*) file_p, pos, mode)){
		return LV_FS_RES_INV_PARAM;
	}
	return 0;

}

lv_fs_res_t FSLVGL::tell_cb(struct _lv_fs_drv_t* drv, void* file_p, uint32_t* pos_p){
	if(ferror((FILE*) file_p)) return LV_FS_RES_NOT_EX;
	auto val = ftell((FILE*) file_p);
	if(val == -1) return LV_FS_RES_UNKNOWN;
	*pos_p = val;
	return 0;
}

void* FSLVGL::dir_open_cb(struct _lv_fs_drv_t* drv, const char* path){
	auto fslvgl = (FSLVGL*) drv->user_data;
	std::string p = std::string(fslvgl->root) + std::string(path);
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
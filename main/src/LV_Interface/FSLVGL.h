#ifndef CLOCKSTAR_FIRMWARE_FSLVGL_H
#define CLOCKSTAR_FIRMWARE_FSLVGL_H

#include <lvgl.h>
#include <string>
#include <unordered_set>

class FSLVGL {
public:
	FSLVGL(char letter);
	virtual ~FSLVGL();

	/**
	 * Allocates memory and stores a file in memory.
	 * @param path Global filesystem path (e.g. /spiffs/file.bin)
	 */
	static void addToCache(const char* path);
	static void removeFromCache(const char* path);

private:
	lv_fs_drv_t drv;                   /*Needs to be static or global*/
	const std::string Root = "/spiffs";
	struct RamFile {
		uint8_t* data = nullptr;
		size_t seekHead = 0;
		const char* path;
		size_t size;
	};
	static std::unordered_set<RamFile*> cache;


	static bool ready_cb(struct _lv_fs_drv_t* drv);
	static void* open_cb(struct _lv_fs_drv_t* drv, const char* path, lv_fs_mode_t mode);
	static lv_fs_res_t close_cb(struct _lv_fs_drv_t* drv, void* file_p);
	static lv_fs_res_t read_cb(struct _lv_fs_drv_t* drv, void* file_p, void* buf, uint32_t btr, uint32_t* br);
	static lv_fs_res_t write_cb(struct _lv_fs_drv_t* drv, void* file_p, const void* buf, uint32_t btw, uint32_t* bw);
	static lv_fs_res_t seek_cb(struct _lv_fs_drv_t* drv, void* file_p, uint32_t pos, lv_fs_whence_t whence);
	static lv_fs_res_t tell_cb(struct _lv_fs_drv_t* drv, void* file_p, uint32_t* pos_p);
	static void* dir_open_cb(struct _lv_fs_drv_t* drv, const char* path);
	static lv_fs_res_t dir_read_cb(struct _lv_fs_drv_t* drv, void* rddir_p, char* fn);
	static lv_fs_res_t dir_close_cb(struct _lv_fs_drv_t* drv, void* rddir_p);
};


#endif //CLOCKSTAR_FIRMWARE_FSLVGL_H

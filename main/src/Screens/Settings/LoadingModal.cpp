#include "LoadingModal.h"
#include "Settings/Settings.h"

LoadingModal::LoadingModal(LVScreen *parent) : LVModal(parent) {
	text = new LabelElement(*this, "Loading...", [](){}, false, LV_ALIGN_CENTER);

	lv_obj_set_align(*text, LV_ALIGN_CENTER);
}

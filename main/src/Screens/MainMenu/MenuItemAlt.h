#ifndef CLOCKSTAR_FIRMWARE_MENUITEMALT_H
#define CLOCKSTAR_FIRMWARE_MENUITEMALT_H

#include "MenuItem.h"
#include <string>

class MenuItemAlt : public MenuItem {
public:
	MenuItemAlt(lv_obj_t* parent, const char* gifPath, const char* labelPath);
	void setAltPaths(const char* gifPathAlt, const char* labelPathAlt);
	void setAltLabel(const char* gifPathAlt, const char* labelTextAlt);

private:
	const std::string gifPath;
	const std::string labelPath;
	std::string gifPathAlt;
	std::string labelPathAlt;
	std::string labelTextAlt;

	lv_obj_t* textLabel;

	void onClick();
	void onDefocus() override;

	void setOrig();
	void setAlt();

	bool isAlt = false;

};


#endif //CLOCKSTAR_FIRMWARE_MENUITEMALT_H

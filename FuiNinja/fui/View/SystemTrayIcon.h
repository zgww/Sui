#pragma once

#include "../Core/Predef.h"
#include "../Core/Mouse.h"
#include "../Core/Vec2.h"
#include <string>




class SystemTrayIcon : public GcObj {
public:
	int uid = 0;
	void* data = nullptr;
	std::string iconPath;

	SystemTrayIcon();
	void setIconPath(const char* path);
	bool init();
	void destroy();

	virtual const char* getClassName() const { return "SystemTrayIcon"; }
};

std::vector<SystemTrayIcon*> SystemTrayIcons_use();
SystemTrayIcon* SystemTrayIcons_findByUid(int uid);
void SystemTrayIcon_onMouseData(MouseData* md);

#include "./SystemTrayIcon_orc.h"
#include <windowsx.h>
#include <windows.h>
#include <string>
#include <winuser.h>
#include "Naga/Utf8Util.h"
#include "../Core/App_orc.h"
#include "../Core/Defines_win.h"
// #include <windowsx.h>


class TrayData {
public:
    NOTIFYICONDATAA notifyIconData;
};

static 
TrayData* getData(SuiView$SystemTrayIcon* self){
    return (TrayData*)self->data;
}

void  SuiView$SystemTrayIcon$dtor(SuiView$SystemTrayIcon *  self){
    auto td = getData(self);
    if (td){
        delete td;
        self->data = NULL;
    }
}
bool SuiView$SystemTrayIcon$initData(SuiView$SystemTrayIcon *  self){
    if (!self->iconPath){
        return false;
    }

    auto td = new TrayData();
    self->data = td;


	memset(&td->notifyIconData, 0, sizeof(td->notifyIconData));
	td->notifyIconData.cbSize = sizeof(td->notifyIconData);

	td->notifyIconData.uID = self->uid;//IDI_ICON_MY;
    //参数意思：https://learn.microsoft.com/zh-cn/windows/win32/api/shellapi/ns-shellapi-notifyicondataa
	td->notifyIconData.uCallbackMessage = SUI_WM_TRAYICON;

	// set handle to the window that receives tray icon notifications
	td->notifyIconData.hWnd = GetForegroundWindow();

	// fields that are being set when adding tray icon 
	td->notifyIconData.uFlags = NIF_MESSAGE | NIF_ICON;// | NIF_TIP;
	//auto icon = LoadIcon(NULL, MAKEINTRESOURCE(IDI_ICON1));
	auto hInstance = GetModuleHandle(NULL);
	// auto icon = LoadIcon(hInstance, (LPCTSTR)IDI_ICON_MY);

    auto exeDir = Utf8Util::toutf16(self->iconPath->str);
    // auto exePath = FsUtil::getExecutionPath();
    // auto exeDir = Path(exePath).dirname().append("icon1.ico")._wpath;
    auto icon2 = (HICON)LoadImageW(NULL, exeDir.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);

    // set image
    td->notifyIconData.hIcon = icon2;

	if (!td->notifyIconData.hIcon)
		return FALSE;

	td->notifyIconData.uVersion = NOTIFYICON_VERSION_4;

	if (!Shell_NotifyIconA(NIM_ADD, &td->notifyIconData))
		return FALSE;

	Shell_NotifyIconA(NIM_SETVERSION, &td->notifyIconData);
    return true;
}
bool  SuiView$SystemTrayIcon$doDestroy(SuiView$SystemTrayIcon *  self){
    auto td = getData(self);
    if (td){
        bool ok = Shell_NotifyIconA(NIM_DELETE, &td->notifyIconData);
        return ok;
    }
    return true;
}
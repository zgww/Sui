#include "./MenuNative_orc.h"
#include <windowsx.h>
#include <windows.h>
#include <string>
#include <winuser.h>
#include "Naga/Utf8Util.h"
#include "../Core/App_orc.h"
// #include <windowsx.h>



static void _create_menu(HMENU parent, SuiView$MenuNativeItem* item) {
    //MENUINFO info;
   /* auto ok = SetMenuInfo(
        parent,
        &info
    );*/

    int l = item->children->size(item->children);

    for (int i = 0; i < l; i++){
        SuiView$MenuNativeItem *kid = (SuiView$MenuNativeItem *)item->children->get(item->children, i);
        int kidsSize = kid->children->size(kid->children);
        wchar_t *label = new_Utf8Util_toutf16(kid->label->str);
        //子菜单
        if (kidsSize > 0){
            HMENU kid_menu = CreatePopupMenu();
            _create_menu(kid_menu, kid);
            AppendMenuW(parent, MF_POPUP|MF_STRING, (UINT)kid_menu, label);
        } else { //叶子菜单
            AppendMenuW(parent, MF_STRING, kid->commandId, label);
        }
        free(label);
    }
}
long long  SuiView$MenuNative$buildNativeMenu(SuiView$MenuNative * self, SuiView$MenuNativeItem * root){

    HMENU menu = CreatePopupMenu();
    _create_menu(menu, root);

    return (long long)menu;
}

static LRESULT HookProc(int code, WPARAM wp, LPARAM lp) {
    if (code == MSGF_MENU) {
        PMSG pMsg = (PMSG)lp;
        if (pMsg->message == WM_MOUSEMOVE) {
            auto clientX = (int)(short)LOWORD(lp);
            auto clientY = (int)(short)HIWORD(lp);



            // URGC_VAR_CLEANUP SuiCore$App *app = NULL;
            // SuiCore$App_use(&app);
            // app->layoutAndDrawAllWindows(app);

            //auto win = get_window_by_hwnd(pMsg->hwnd);
            //auto r = win->getClientRect();

            POINT p = {0};
            ClientToScreen(pMsg->hwnd, &p);
            // GetWindowRect(pMsg->hwnd, &rect);

            RECT clientRect = {};
            GetClientRect(pMsg->hwnd, &clientRect);

            auto screenX = GET_X_LPARAM(pMsg->lParam);
            auto screenY = GET_Y_LPARAM(pMsg->lParam);
            SuiCore$MouseData md = { 0 };
            md.clientX = screenX - p.x;
            md.clientY = screenY - p.y;
            md.button = 0;
            md.isMouseMove = true;
            md.windowId = (long long)pMsg->hwnd;

            // printf("HOokProc WM_MOUSEMOVE. %d,%d. %d,%d\n", clientX, clientY
            // , md.clientX, md.clientY);

            SuiCore$Mouse_onMouseMove(md);

            SuiCore$App_repaintWindowById((long long)pMsg->hwnd);
            // App::ins()->_remap_up_position.remap_onmove(&e);
            // e.dispatchMouseMove();


            //printf("mousemove hook: %d %d window:%d\n", e.client_x, e.client_y, win->getId());
            //_mouse_move(win, pMsg->wParam, pMsg->lParam);
        }

    }
    return CallNextHookEx(NULL, code, wp, lp);

}

// void SuiView$MenuNative$show(SuiView$MenuNative * self){
//     HWND win = GetActiveWindow();
//     POINT point;
//     GetCursorPos(&point);
//     RECT rect;
//     GetWindowRect(win, &rect);
//     int x = point.x - rect.left;
//     int y = point.y - rect.top;

//     HMENU menu = (HMENU)self->id;

//     auto hook = SetWindowsHookEx(WH_MSGFILTER, HookProc, NULL, GetCurrentThreadId());
//     auto ret = TrackPopupMenu(menu, 
//         TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
//         point.x, point.y, 0, win, NULL);
//     UnhookWindowsHookEx(hook);
//     //到了这里，菜单已经消失了
//     self->onDismiss(self);
// }

void SuiView$MenuNative$showAt(SuiView$MenuNative * self, int clientX, int clientY){

    HWND win = GetActiveWindow();
    // POINT point;
    // GetCursorPos(&point);
    RECT rect;
    GetWindowRect(win, &rect);

    POINT p = { 0 };
    p.x = clientX;
    p.y = clientY;
    ClientToScreen(win, &p);

    int screenX = clientX + rect.left;
    //int screenY = 0 + rect.top;

     //SuiView$MenuNative$showAtScreenPosition(self, screenX, screenY);
    SuiView$MenuNative$showAtScreenPosition(self, p.x, p.y);
}
void SuiView$MenuNative$showAtScreenPosition(SuiView$MenuNative * self, int screenX, int screenY){
    HWND win = (HWND)self->windowId;
    if (!win){
        win = GetActiveWindow();
    }
    SetForegroundWindow(win);////解决在菜单外单击左键菜单不消失的问题
    // self->windowId = (long long)win;
    HMENU menu = (HMENU)self->id;

    auto hook = SetWindowsHookEx(WH_MSGFILTER, HookProc, NULL, GetCurrentThreadId());
    auto ret = TrackPopupMenu(menu, 
        TPM_LEFTALIGN | TPM_RIGHTBUTTON, 
        screenX, screenY, 0, win, NULL);
    UnhookWindowsHookEx(hook);
    self->onDismiss(self);
}
void SuiView$MenuNative$destroy(SuiView$MenuNative * self){
    printf("============do destroy menu\n");

    EndMenu();
    if (self->windowId){
        // SendMessage((HWND)self->windowId, WM_CANCELMODE, 0, 0);
        self->windowId = 0;
    }
    if (self->id){
        HMENU menu = (HMENU)self->id;
        DestroyMenu(menu);
        self->id = 0;
    }
}
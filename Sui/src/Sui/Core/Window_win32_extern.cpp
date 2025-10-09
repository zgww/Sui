#include <stdio.h>
#include <string>
#include <chrono>

// #include <assimp/Importer.hpp>      // C++ importer interface
// #include <assimp/scene.h>           // Output data structure
// #include <assimp/postprocess.h>     // Post processing flags


// #include "../../pch.h"
#include "../../GL/glew.h"
#include "../../GL/wglew.h"
#include "../../nanovg/nanovg.h"
#include "nanovg/nanovg.h"
// #define NANOVG_GL2 1
#define NANOVG_GL3_IMPLEMENTATION
#include "../../nanovg/nanovg_gl.h"

#include "./Defines_win.h"
#include "linmath.h"

#include <string.h>
#include "./Window_orc.h" 
#include "Naga/Utf8Util.h"
#include "Naga/Win32Utf8Util.h"
#include "urgc_api.h"
#include "../Core/Global_orc.h"
#include "../Core/View_orc.h"
#include "../Dialog/MessageDialog_orc.h"
#include "./App_orc.h"
#include "./Mouse_orc.h"
#include "./Keyboard_orc.h"
#include "./KeyEvent_orc.h"
#include "../View/MenuNative_orc.h"
#include "../View/SystemTrayIcon_orc.h"

#include <windowsx.h>
#include <windows.h>

#include "GL/GL.h"
#include "GL/glew.h"


#include <dwmapi.h>
#include <CommCtrl.h>
#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "Imm32.lib")
#pragma comment(lib, "comctl32.lib")

#define CLASS_NAME "suiWindow"


// 函数指针声明
typedef BOOL(WINAPI* PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC hdc, const int* piAttribIList, const FLOAT* pfAttribFList, UINT nMaxFormats, int* piFormats, UINT* nNumFormats);
typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC hDC, HGLRC hShareContext, const int* attribList);

// 函数指针
// typedef BOOL(WINAPI* PFNWGLGETPIXELFORMATATTRIBIVARBPROC)(
//     HDC hDC,              // 设备上下文
//     int iPixelFormat,     // 要查询的像素格式编号
//     int iLayerPlane,      // 通常为 0（主平面）
//     int nAttributes,      // 属性数量
//     const int* piAttributes,  // 属性列表（如 WGL_SAMPLE_BUFFERS_ARB）
//     int* piValues         // 输出：对应的属性值
//     );
static PFNWGLGETPIXELFORMATATTRIBIVARBPROC wglGetPixelFormatAttribivARB = nullptr;

static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;



// static Assimp::Importer importer;
// static const aiScene* ImportModel( const std::string& pFile) {
//   // Create an instance of the Importer class

//   // And have it read the given file with some example postprocessing
//   // Usually - if speed is not the most important aspect for you - you'll
//   // probably to request more postprocessing than we do in this example.
//   const aiScene* scene = importer.ReadFile( pFile,
//     aiProcess_CalcTangentSpace       |
//     aiProcess_Triangulate            |
//     aiProcess_JoinIdenticalVertices  |
//     aiProcess_SortByPType);
//   auto n = scene->mRootNode;

//   // If the import failed, report it
//   if (nullptr == scene) {
//     // DoTheErrorLogging( importer.GetErrorString());
//     // return false;
//     return nullptr;
//   }
// //   std::shared_ptr<aiScene> ret{(aiScene*)scene};
// //   return ret;
//     return scene;

//   // Now we can access the file's contents.
// //   DoTheSceneProcessing( scene);

//   // We're done. Everything will be cleaned up by the importer destructor
// //   return true;
// }

class CostUs {
public:
  std::vector<long long> timepoints;
  std::vector<std::string> labels;

  CostUs() {
    stat("");
  }
  void stat(std::string str) {
    long long us = std::chrono::duration_cast<std::chrono::microseconds>(
      std::chrono::system_clock::now().time_since_epoch()
    ).count();
    timepoints.push_back(us);

    labels.push_back(str);
  }
  void print(std::string title) {
    printf("-------------%s----------\n", title.c_str());
    long long startUs = timepoints[0];
    for (int i = 1; i < labels.size(); i++) {
      long long prevUs = timepoints[i - 1] ;
      long long nowUs = timepoints[i] ;
      double cost = ((double)(nowUs - prevUs)) / 1000.0;
      double costTotal = ((double)(nowUs - startUs)) / 1000.0;
      printf("\t%40s:\t\t\t\t%8fms/%8fms\n", labels[i].c_str(), cost, costTotal);
    }
  }
};

typedef struct
{
    HWND hwnd;
    HDC hdc;
    HGLRC hrc;
    NVGcontext *vg;
    float devicePixelRatio;
} WindowDataWin32;
//
//static void draw(HWND hwnd, NVGcontext *vg)
//{
//    static int offset = 0;
//    // offset+=1;
//    RECT rect = {0};
//    GetWindowRect(hwnd, &rect);
//
//    float w = rect.right - rect.left;
//    float h = rect.bottom - rect.top;
//
//    glViewport(0, 0, w, h);
//
//    glClearColor(.2f, 0.f, 0.f, 0.f);
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    nvgBeginFrame(vg, w, h, w / h);
//
//    nvgFillColor(vg, nvgRGB(255, 0, 255));
//    float x = 50 + offset;
//    nvgBeginPath(vg);
//    nvgRect(vg, x, 50, 200, 200);
//    nvgFill(vg);
//    nvgEndFrame(vg);
//    // printf("swap offset:%d x:%f\n", offset, x);
//    SwapBuffers(GetDC(hwnd));
//}

static HWND _createWindow();
//
//void hideWindow(HWND win);
//void minWindow(HWND win);
//void maxWindow(HWND win);
//static void showWindow(HWND hwnd);

//void SuiCore$testCursor();
//void SuiCore$testMouse();

class GetAssisKey {
public:
    GetAssisKey() {
        lctrl = (GetKeyState(VK_LCONTROL) & 0x8000);
        rctrl = (GetKeyState(VK_RCONTROL) & 0x8000);
        lshift = (GetKeyState(VK_LSHIFT) & 0x8000);
		rshift = (GetKeyState(VK_RSHIFT) & 0x8000);
        lalt = (GetKeyState(VK_MENU) & 0x8000);
		ralt =  (GetKeyState(VK_RMENU) & 0x8000);

        ctrl = lctrl || rctrl;
        shift = lshift || rshift;
        alt = lalt || ralt;
    }
    bool lctrl = false;
    bool rctrl = false;
    bool ctrl = false;
    bool lshift = false;
    bool rshift = false;
    bool shift = false;

    bool lalt = false;
    bool ralt = false;
    bool alt = false;
};

static std::string _vk_to_key(int code) {
    if (code >= '0' && code <= '9') {
        return std::string() + (char)(code);
    }
    if (code >= VK_NUMPAD0 && code <= VK_NUMPAD9) {
        return std::string() + (char)('0' + code - VK_NUMPAD0);
    }
    if (code >= 'A' && code <= 'Z') {
        return std::string() + (char)(code);
    }
    if (code == VK_SPACE) return " ";
    if (code == VK_OEM_1) return ";";
    if (code == VK_OEM_PLUS) return "+";
    if (code == VK_OEM_COMMA) return ",";
    if (code == VK_OEM_MINUS) return "-";
    if (code == VK_OEM_PERIOD) return ".";
    if (code == VK_OEM_2) return "/";
    if (code == VK_OEM_3) return "`";
    if (code == VK_OEM_4) return "[";
    if (code == VK_OEM_5) return "\\";
    if (code == VK_OEM_6) return "]";
    if (code == VK_RETURN) return "return";
    if (code == VK_BACK) return "backspace";
    if (code == VK_ESCAPE) return "esc";
    if (code == VK_LEFT) return "left";
    if (code == VK_RIGHT) return "right";
    if (code == VK_DOWN) return "down";
    if (code == VK_UP) return "up";
    return "";
}

static int _key_down(HWND hwnd, WPARAM wp, LPARAM lp) {
    GetAssisKey ak;

    SuiCore$KeyboardData kd = { 0 };
    std::string key = _vk_to_key(wp);
    kd.char_code = wp;
    //临时字符串指针，需要小心
    kd.key = key.c_str();
    kd.windowId = (long long)hwnd;
    kd.isKeyDown = true;
    kd.isKeyUp = false;

    kd.ctrl = ak.ctrl;
    kd.shift = ak.shift;
    kd.alt = ak.alt;

    SuiCore$Keyboard_onKeyDown(&kd);

    printf("键盘事件 ctrl:%d, shift:%d, alt:%d, :code:%d key:%s\n", 
        kd.ctrl, kd.shift, kd.alt, kd.char_code, kd.key);
    //e.dispatch();
    return 0;
}
static int _key_up(HWND hwnd, WPARAM wp, LPARAM lp) {
    GetAssisKey ak;

    SuiCore$KeyboardData kd = { 0 };
    std::string key = _vk_to_key(wp);
    kd.char_code = wp;
    //临时字符串指针，需要小心
    kd.key = key.c_str();
    kd.windowId = (long long)hwnd;
    kd.isKeyDown = false;
    kd.isKeyUp = true;

    kd.ctrl = ak.ctrl;
    kd.shift = ak.shift;
    kd.alt = ak.alt;
    if (ak.alt ){
        printf("alt ...\n");
    }

    SuiCore$Keyboard_onKeyDown(&kd);

    printf("键盘事件 ctrl:%d, shift:%d, alt:%d, :code:%d key:%s\n", 
        kd.ctrl, kd.shift, kd.alt, kd.char_code, kd.key);
    //e.dispatch();
    return 0;
}

static LRESULT _mouse_down(HWND hwnd, int button, WPARAM wParam, LPARAM lp)
{
    SuiCore$MouseData md = { 0 };

    //md.eventType = "mousedown";
    md.button = button;
    md.clientX = GET_X_LPARAM(lp);
    md.clientY = GET_Y_LPARAM(lp);
    md.windowId = (long long)hwnd;
    md.isMouseDown = true;

    GetAssisKey ak;
    md.ctrl = ak.ctrl;
    md.shift = ak.shift;
    md.alt = ak.alt;

    SuiCore$printMouseData(&md, "_mousedown");

    //捕获事件
    if (hwnd){
        SetCapture(hwnd);
    }

    SuiCore$Mouse_onMouseDown(md);
    return 0;
}
static void _build_md_for_ontrayicon(
    SuiCore$MouseData *md,
    HWND hwnd, WPARAM wp, LPARAM lp, int button
    , int type//0:down,1:move,2:up, 3: dblclick
    ){
    // SuiCore$MouseData md = { 0 };
    auto msg = LOWORD(lp);
    auto uid = HIWORD(lp);

    //md.eventType = "mousedown";
    md->button = button;
    md->clientX = GET_X_LPARAM(wp);
    md->clientY = GET_Y_LPARAM(wp);
    md->windowId = (long long)hwnd;
    md->isMouseDown = type == 0;
    md->isMouseMove = type == 1;
    md->isMouseUp = type == 2;
    md->isDoubleClick = type == 3;

    GetAssisKey ak;
    md->ctrl = ak.ctrl;
    md->shift = ak.shift;
    md->alt = ak.alt;
}
static LRESULT _ontrayicon(HWND hwnd, WPARAM wp, LPARAM lp)
{
    auto msg = LOWORD(lp);
    auto uid = HIWORD(lp);
    SuiCore$MouseData md = { 0 };
    md.button = -1;
    md.uid = uid;

    //注意。 实际上并不会在按下时，就触发事件。而是在up时，同时触发down/up
    if (msg == WM_LBUTTONDOWN){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 1, 0); }
    if (msg == WM_MBUTTONDOWN){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 2, 0); }
    if (msg == WM_RBUTTONDOWN){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 3, 0); }

    if (msg == WM_MOUSEMOVE){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 1, 1); }

    if (msg == WM_LBUTTONUP){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 1, 2); }
    if (msg == WM_MBUTTONUP){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 2, 2); }
    if (msg == WM_RBUTTONUP){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 3, 2); }

    if (msg == WM_LBUTTONDBLCLK){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 1, 3); }
    if (msg == WM_MBUTTONDBLCLK){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 2, 3); }
    if (msg == WM_RBUTTONDBLCLK){ _build_md_for_ontrayicon(&md, hwnd, wp, lp, 3, 3); }

    if (md.button != -1){//说明是鼠标相关事件
        // if (md.isDoubleClick){
        //     POINT pt{};
        //     GetCursorPos(&pt);//取鼠标坐标
        //     ::SetForegroundWindow(hwnd);//解决在菜单外单击左键菜单不消失的问题
        //     auto hMenu = CreatePopupMenu();//生成菜单
        //     //为托盘菜单添加两个选项
        //     AppendMenu(hMenu, MF_STRING, 1, TEXT("update"));
        //     AppendMenu(hMenu, MF_STRING, 2, TEXT("show"));
        //     AppendMenu(hMenu, MF_STRING, 3, TEXT("about"));
        //     auto id = TrackPopupMenu(hMenu, TPM_RETURNCMD, pt.x, pt.y, NULL, hwnd, NULL);
        //     printf("on menu activate:%d\n", id);
        // }
        SuiCore$printMouseData(&md, "_mousedown");
        SuiView$SystemTrayIcon_onMouseData(md);
    }
    return 0;
}



static LRESULT _mouse_up(HWND hwnd, int button, WPARAM wParam, LPARAM lp)
{
    SuiCore$MouseData md = { 0 };

    //md.eventType = "mousedown";
    md.button = button;
    md.clientX = GET_X_LPARAM(lp);
    md.clientY = GET_Y_LPARAM(lp);
    md.windowId = (long long)hwnd;
    md.isMouseUp = true;

    GetAssisKey ak;
    md.ctrl = ak.ctrl;
    md.shift = ak.shift;
    md.alt = ak.alt;

    SuiCore$printMouseData(&md, "_mouseup");

    //捕获事件
    ReleaseCapture();

    SuiCore$Mouse_onMouseUp(md);
  
    return 0;
}

static LRESULT _mouse_move(HWND hwnd,  WPARAM wParam, LPARAM lp)
{
    SuiCore$MouseData md = { 0 };

    //printf("收到move事件\n");

    //md.eventType = "mousedown";
    md.clientX = GET_X_LPARAM(lp);
    md.clientY = GET_Y_LPARAM(lp);
    md.windowId = (long long)hwnd;
    md.isMouseMove = true;

    GetAssisKey ak;
    md.ctrl = ak.ctrl;
    md.shift = ak.shift;
    md.alt = ak.alt;

    //SuiCore$printMouseData(&md, "_mousemove");

    SuiCore$Mouse_onMouseMove(md);

    return 0;
}
static
std::string _toutf8(wchar_t *wstr){
    const char *str = new_Utf8Util_toutf8(wstr);
    std::string ret = str;
    free((void*)str);
    return ret;
}
static
std::string _utf32_to_utf8(wchar_t wchar){
    const char *str = new_Utf8Util_utf32ToUtf8(wchar);
    std::string ret = str;
    free((void*)str);
    return ret;
}
static std::string
_char_surrogate_to_utf8(UINT32 high_surrogate, UINT32 low_surrogate)
{
    const UINT32 SURROGATE_OFFSET = 0x10000 - (0xD800 << 10) - 0xDC00;
    const UINT32 codepoint = (high_surrogate << 10) + low_surrogate + SURROGATE_OFFSET;
    // return Utf8Util::utf32_to_utf8(codepoint);
    return _utf32_to_utf8(codepoint);
}
/*把WPARAM当成 当前编码页的 双字节字符，转为unicode 16*/
static int Ime_WPARAM_asActiveCodePage_toWchar(WPARAM wParam) {
    char tmp[4] = { 0 };
    tmp[0] = (wParam >> 8)&0xff;
    tmp[1] = (wParam >> 0)&0xff;

    wchar_t* wstr = new_Win32Utf8Util_acpToUtf16(tmp);
    wchar_t wchar = wstr[0];
    free(wstr);
    return wchar;
}
/*输入输入法字符
https://learn.microsoft.com/zh-cn/windows/win32/intl/wm-ime-char
要求创建Unicode窗体
*/
static int _ime_char(HWND hwnd, WPARAM wParam, LPARAM lp) {
    //wchar_t wchar = wParam;

    //dbcs窗口（非unicode窗口）， wParam是双字节编码。应该是跟active code page 有关
    wchar_t wchar = Ime_WPARAM_asActiveCodePage_toWchar(wParam);

    std::string text = _utf32_to_utf8(wchar);

    SuiCore$dispatchTextInputEvent(text.c_str(), (long long)hwnd);

    // TextInputEvent e;
    // e.text = text;
    // e.window = win;
    // printf("textinput wchar:%s\n", e.text.c_str());
    // e.dispatch();
    return 0;
}
/*输入字符,不含输入法字符*/
static int _char(HWND hwnd, WPARAM wParam, LPARAM lp) {
    GetAssisKey ak;
    if (ak.alt || ak.ctrl) {
        return 0;
    }

    wchar_t wchar = wParam;
    std::string text = _utf32_to_utf8(wchar);
    SuiCore$dispatchTextInputEvent(text.c_str(), (long long)hwnd);
    return 0;

    // TextInputEvent e;
    // e.text = text;
    // e.window = win;
    // printf("textinput char:%s\n", e.text.c_str());
    // e.dispatch();
    // return 0;
}
static void _ime_end_composition(HWND hwnd, WPARAM wp, LPARAM lp) {
    printf("结束合成，发送空TextEditing事件\n");
    // TextEditingEvent e;
    // e.dispatch();
    SuiCore$dispatchImeEndComposition((long long)hwnd);
}
static void _ime_composition(HWND hwnd, WPARAM wp, LPARAM lp) {

    auto himc = ImmGetContext(hwnd);
    auto result_length = ImmGetCompositionStringW(himc, GCS_RESULTSTR, NULL, 0);
    //字节长
    auto ori_length = ImmGetCompositionStringW(himc, GCS_COMPSTR, NULL, 0);
    wchar_t ori_buf[256] = { 0 };
    auto ori_length2 = ImmGetCompositionStringW(himc, GCS_COMPSTR, ori_buf, sizeof(ori_buf));
    auto cursor_pos = ImmGetCompositionStringW(himc, GCS_CURSORPOS, NULL, 0);
    auto text = _toutf8(ori_buf);

    printf("合成输入中 :%ld %ld cursor:%ld  %ld text=%s\n",
       result_length, ori_length, cursor_pos, ori_length2, text.c_str());
    ImmReleaseContext(hwnd, himc);

    auto rune_len = ori_length / sizeof(wchar_t);

    SuiCore$dispatchImeComposition(
        text.c_str(),
        cursor_pos,
        rune_len - cursor_pos,
        (long long)hwnd
    );
    // TextEditingEvent e;
    // e.text = text;
    // e.start = cursor_pos;
    // e.length = rune_len - e.start;
    // e.window = win;
    // printf("textediting:%s, start:%d,length:%d\n", e.text.c_str(), e.start, e.length);
    // e.dispatch();
}
static int _set_focus(HWND hwnd, WPARAM wp, LPARAM lp) {
    printf("取得窗口焦点:%p\n", hwnd);
    // WindowFocusGainedEvent().dispatch(win);
    Sui$dispatchWindowFocusGainedEvent((long long)hwnd);
    return 0;
}

static int _kill_focus(HWND hwnd, WPARAM wp, LPARAM lp) {
    printf("丢失窗口焦点:%p\n", hwnd);
    Sui$dispatchWindowFocusLostEvent((long long)hwnd);
    // WindowFocusLostEvent().dispatch(win);
    return 0;
}
static int _mouse_wheel(HWND hwnd, WPARAM wParam, LPARAM lp) {
    SuiCore$MouseData md = { 0 };

    //printf("收到move事件\n");

    //md.eventType = "mousedown";
    md.clientX = GET_X_LPARAM(lp);
    md.clientY = GET_Y_LPARAM(lp);
    md.windowId = (long long)hwnd;
    md.isMouseMove = true;

    GetAssisKey ak;
    md.ctrl = ak.ctrl;
    md.shift = ak.shift;
    md.alt = ak.alt;

    RECT r = {0};
    GetWindowRect(hwnd, &r);

    // RECT cr = {0};
    // GetClientRect(hwnd, &cr);

    POINT p = {0};
    ClientToScreen(hwnd, &p);
    
    // auto r = win->getClientRect();
    //wheel 取到的是屏幕坐标
    // e.shift = ak.shift;
    md.clientX = GET_X_LPARAM(lp) - p.x;
    md.clientY = GET_Y_LPARAM(lp) - p.y;

    //SuiCore$printMouseData(&md, "_mousemove");

    //滚一次，120, 快速滚，可能出现360, 600
    int delta= GET_WHEEL_DELTA_WPARAM(wParam);

    SuiCore$Mouse_onWheel(&md, 0, delta);


    // e.delta_x = 0;
    //滚一次，120, 快速滚，可能出现360, 600
    // e.delta_y = delta / 120;// delta > 0 ? 1 : -1;
    // e.window = win;
    // printf("wheel: x:%d y:%d delta:%d\n", e.delta_x, e.delta_y, delta);
    // e.dispatch();

    // int windowId = win->getId();

    // //在下一帧触发.等wheel 生效了
    // Timer::setTimeout(CLOSURE([windowId, e](Timer* t) {
    //     //同时派发move事件.滚动视图内部才能更新hover
    //     MouseEvent movevt;
    //     movevt.type = "mousemove";
    //     movevt.client_x = e.client_x;
    //     movevt.client_y = e.client_y;
        
    //     movevt.button = 0;
    //     movevt.window = App::ins()->windowMgr->getWindowById(windowId);
    //     movevt.dispatchMouseMove();
    //     }), 10);
    return 0;
}

static int _command(HWND win, WPARAM wp, LPARAM lp) {


    auto ok = IDOK;
    auto cancel = IDCANCEL;
    auto type = HIWORD(wp);
    auto realid = LOWORD(wp);

    int id = wp;

    SuiView$MenuNative_doCommand((long long)win, id);
   /* if (g_current_native_menu) {

        auto item = g_current_native_menu->root->by_id(id);
        if (item) {
            if (item->click) {
                try {
                    item->click->call();
                }
                catch (std::exception& e) {
                    printf("_command捕获到异常:%s\n", e.what());
                }
            }
        }
        g_current_native_menu = nullptr;
    }*/
    return 0;
}
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // auto win = get_window_by_hwnd(hwnd);
    Sui$Window* self = (Sui$Window*)GetProp(hwnd, "Sui$Window");
    void *win = NULL;
    if (1 || win)
    {
        switch (uMsg)
        {

        //阴影
        case WM_ACTIVATE:
        {
            if (self && self->borderless){
                MARGINS margins = {1, 1, 1, 1};
                HRESULT hr = S_OK;

                hr = DwmExtendFrameIntoClientArea(hwnd, &margins);
                return hr;
            }
            break;
            
        }

        case WM_NCCALCSIZE:
        {
            if (self && self->borderless){
                if (wParam)
                {
                    NCCALCSIZE_PARAMS* lp = (LPNCCALCSIZE_PARAMS)lParam;
                    if (IsZoomed(hwnd))//最大化时修正客户区外边距
                    {
                        lp->rgrc[0].left += 8;
                        lp->rgrc[0].top += 8;
                        lp->rgrc[0].right -= 8;
                        lp->rgrc[0].bottom -= 8;
                    }
                }
                return 0;//去除非客户区
            }
            break;
        }

        case WM_NCHITTEST:
		{
            if (self && self->borderless){
                //处理resize
                //标记只处理resize
                bool isResize = false;

                //鼠标点击的坐标
                POINT ptMouse = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
                //窗口矩形
                RECT rcWindow;
                GetWindowRect(hwnd, &rcWindow);
                RECT rcFrame = { 0,0,0,0 };
                AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);
                USHORT uRow = 1;
                USHORT uCol = 1;
                bool fOnResizeBorder = false;

                //确认鼠标指针是否在top或者bottom
                if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + 1)
                {
                    fOnResizeBorder = (ptMouse.y < (rcWindow.top - rcFrame.top));
                    uRow = 0;
                    isResize = true;
                }
                else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - 5)
                {
                    uRow = 2;
                    isResize = true;
                }
                //确认鼠标指针是否在left或者right
                if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + 5)
                {
                    uCol = 0; // left side
                    isResize = true;
                }
                else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - 5)
                {
                    uCol = 2; // right side
                    isResize = true;
                }
                if (ptMouse.x >= rcWindow.left + 300 && ptMouse.x <= rcWindow.right - 135 && ptMouse.y > rcWindow.top + 3 && ptMouse.y <= rcWindow.top + 30)
                {
                    return HTCAPTION;
                }

                LRESULT hitTests[3][3] =
                {
                    { HTTOPLEFT,    fOnResizeBorder ? HTTOP : HTCAPTION,    HTTOPRIGHT },
                    { HTLEFT,       HTNOWHERE,     HTRIGHT },
                    { HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT },
                };

                if (isResize == true)
                {
                    return hitTests[uRow][uCol];
                }
                else
                {
                    break;
                }
            }
            break;
		}

        // case WM_NCHITTEST:
        // {
        //     RECT rc; GetClientRect(hwnd, &rc);//客户区矩形
        //     POINT pt; GetCursorPos(&pt); ScreenToClient(hwnd, &pt);//鼠标位置
        //     if (!IsZoomed(hwnd))//最大化时不用调整大小
        //     {
        //         int x = 8;//边框宽度
        //         if (pt.x < rc.left + x)
        //         {
        //             if (pt.y < rc.top + x)return HTTOPLEFT;//左上角
        //             if (pt.y >= rc.bottom - x)return HTBOTTOMLEFT;//左下角
        //             return HTLEFT;//左边,可拖拽
        //         }
        //         if (pt.x >= rc.right - x)//坐标从0开始，所以使用>=
        //         {
        //             if (pt.y < rc.top + x)return HTTOPRIGHT;//右上角
        //             if (pt.y >= rc.bottom - x)return HTBOTTOMRIGHT;//右下角  ,可拖拽
        //             return HTRIGHT;//右边, 可以拖拽
        //         }
        //         if (pt.y < rc.top + x)return HTTOP;//上边, 可以拖拽
        //         if (pt.y >= rc.bottom - x)return HTBOTTOM;//下边, 可以拖拽
        //         if (pt.x >= 400 && pt.y < rc.top + 40) return HTCAPTION;//标题栏,可以移动
        //     }
        //     return HTCLIENT;
        // }

        //case WM_LBUTTONDOWN:
        //    return _mouse_down(hwnd, 1, wParam, lParam);
            // 鼠标
             case WM_LBUTTONDOWN: return _mouse_down(hwnd, 1, wParam, lParam);
             case WM_MBUTTONDOWN: return _mouse_down(hwnd, 2, wParam, lParam);
             case WM_RBUTTONDOWN: return _mouse_down(hwnd, 3, wParam, lParam);
             case WM_LBUTTONUP: return _mouse_up(hwnd, 1, wParam, lParam);
             case WM_MBUTTONUP: return _mouse_up(hwnd, 2, wParam, lParam);
             case WM_RBUTTONUP: return _mouse_up(hwnd, 3, wParam, lParam);
             case WM_MOUSEMOVE: return _mouse_move(hwnd, wParam, lParam);
            // case WM_MOUSELEAVE: return _mouse_leave(win, wParam, lParam);
            //     //滚轮
            case WM_MOUSEWHEEL: return _mouse_wheel(hwnd, wParam, lParam);
            //     //键盘
             case WM_KEYDOWN: return _key_down(hwnd, wParam, lParam);
            /*
            任意字符键
            BACKSPACE 退格
            ENTER（回车）
            ESC 退出
            SHIFT + ENTER（换行）
            TAB*/
             case WM_CHAR: return _char(hwnd, wParam, lParam);
             case WM_KEYUP: return _key_up(hwnd, wParam, lParam);
             case WM_SETFOCUS: return _set_focus(hwnd, wParam, lParam);
             case WM_KILLFOCUS: return _kill_focus(hwnd, wParam, lParam);

            // 输入法
         case WM_IME_CHAR: return _ime_char(hwnd, wParam, lParam);
        case WM_IME_STARTCOMPOSITION:
        {
            // printf("开始合成输入\n");
            // Ime::ins()->set_pos(win, { 0, 100 });
            break;
        }
        case WM_IME_ENDCOMPOSITION:
        {
            _ime_end_composition(hwnd, wParam, lParam);
            break;
        }
        case WM_IME_COMPOSITION:
        {
            _ime_composition(hwnd, wParam, lParam);
            break;
        }
        case WM_IME_SETCONTEXT:
        {
            // 不希望显示CompositionWindow,清除显示CompositionWindow的标记，然后交给DefWindowProc处理
            lParam = lParam & ~ISC_SHOWUICOMPOSITIONWINDOW;
            break;
        }

        // 菜单事件
        case WM_COMMAND:
        {
             return _command(hwnd, wParam, lParam);
        }
            /*  case WM_SYSCOMMAND: {
                  MessageDialog::alert("syscommand");
                  return 0;
              }
              case WM_MENUCOMMAND: {
                  MessageDialog::alert("MENUcommand");
                  return 0;
              }*/
            // case WM_ENTERMENULOOP: {
            //     MessageDialog::alert("WM_ENTERMENULOOP                ");
            //     return 0;
            // }
            // case WM_EXITMENULOOP: {
            //     //MessageDialog::alert("WM_EXITMENULOOP                                 ");
            //     _exit_menu_popup(win, wParam, lParam);
            //     return 0;
            // }
            // 菜单关闭事件
            // case WM_UNINITMENUPOPUP: {
            //     return _uninit_menu_popup(win, wParam, lParam);
            // }

        case WM_SIZE:
        {
            // int width = LOWORD(lParam);  // Macro to get the low-order word.
            // int height = HIWORD(lParam); // Macro to get the high-order word.

            /* WindowResizeEvent e;
             e.dispatch(win);*/

            // ValidateRect(hwnd, NULL); //清空无效区域
            // SuiCore$App_repaintWindowById((long long)hwnd);
            return 0;
        }
        // case WM_ERASEBKGND:
        // {
        //     printf("WM_ERASEBKGND\n");
        //     return 1;
        // }
        case WM_PAINT:
        {
            // draw(hwnd);
            printf("WM_PAINT\n");
            ValidateRect(hwnd, NULL); //清空无效区域
            SuiCore$App_repaintWindowById((long long)hwnd);
            return 0;
            //break;
            // printf("WM_PAINT\n");
            // win->do_drawWindow();
            // return 0;
            // break;
        }
        case WM_CLOSE:
        {
            // 默认的处理就是DestroyWindow
            printf("WM_CLOSE\n");
            // DestroyWindow(hwnd);
            // return 0;
            // WindowCloseEvent().dispatch(win);
            // return 0;
            break;
        }
        case WM_DESTROY: // 已经销毁窗口
        {
            printf("WM_DESTROY:%p\n", hwnd);

            SuiCore$App_onDestroyWindow((long long)hwnd);
            break;
        }
        case SUI_WM_TRAYICON://自定义的托盘消息
        {
            // lParam是消息类型
            return _ontrayicon(hwnd, wParam, lParam);
        }
        
        }
    }
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}

static void _registerWinClass()
{

    HINSTANCE hInstance = GetModuleHandle(0);
    // INITCOMMONCONTROLSEX cx = { sizeof(INITCOMMONCONTROLSEX), ICC_BAR_CLASSES };
    // BOOL ret = InitCommonControlsEx(&cx);

    WNDCLASSA wc = {0};
    wc.style          = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME; // Utf8Util::toutf16(CLASS_NAME).c_str();
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	auto icon = LoadIcon(hInstance, "IDI_ICON1");
    wc.hIcon = icon;
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    WORD ok = RegisterClassA(&wc);
    printf("RegisterClass A ok:%d\n", ok);
}
static void _init()
{
    static bool doinit = true;
    if (doinit)
    {
        doinit = false;
        _registerWinClass();
    }
}
static void setTransparent(HWND hwnd){
    BOOL composition, opaque;

    DWORD color;
    DwmIsCompositionEnabled(&composition);;
    auto v = DwmGetColorizationColor(&color, &opaque);
    HRGN region = CreateRectRgn(0, 0, -1, -1);
    DWM_BLURBEHIND bb = { 0 };
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    bb.hRgnBlur = region;
    bb.fEnable = TRUE;

    DwmEnableBlurBehindWindow(hwnd, &bb);
    DeleteObject(region);
}
static HWND _createWindow()
{


    DWORD style = 0;

    style = 
        // WS_POPUP
        WS_OVERLAPPEDWINDOW
        ;// | WS_VISIBLE; //WS_VISIBLE会立即触发WM_PAINT; 初始宽高未设置好的话，就会闪烁
        // style = WS_POPUP;
    HWND hwnd = CreateWindowExA(
        // WS_EX_APPWINDOW //| WS_EX_LAYERED,
        0,                          // Optional window styles.
        CLASS_NAME,                 // Window class
        "Learn to Program Windows", // Window text
        style ,                      // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,               // Parent window
        NULL,               // Menu
        GetModuleHandle(0), // Instance handle
        NULL                // Additional application data
    );


    if (1){
    }

    return hwnd;
}


static HGLRC sharehrc = NULL; //共享的渲染上下文
static void _enable_opengl(HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    // LoadLibrary("OpenGL32.dll");
    //  get the device context (DC)
    *hDC = GetDC(hWnd);
    printf("初始化glew \n");
    //_initGlewOnce();
    printf("初始化glew完成 \n");

    // if (sharehrc){
    //     *hRC = sharehrc;
    //     return;
    // }

    if (1){
        PIXELFORMATDESCRIPTOR pfd = {
            sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
            1,                             // version number
            PFD_DRAW_TO_WINDOW |           // support window
                PFD_SUPPORT_OPENGL |       // support OpenGL
                PFD_SUPPORT_COMPOSITION |         // Format Must Support Composition
                PFD_DOUBLEBUFFER,          // double buffered
            PFD_TYPE_RGBA,                 // RGBA type
            32,                            // 24-bit color depth
            0, 0, 0, 0, 0, 0,              // color bits ignored
            8, //8,                             // no alpha buffer

            0,                             // shift bit ignored
            0,                             // no accumulation buffer
            0, 0, 0, 0,                    // accum bits ignored
            24,                            // 32-bit z-buffer
            8,                             // no stencil buffer
            0,                             // no auxiliary buffer
            PFD_MAIN_PLANE,                // main layer
            0,                             // reserved
            0, 0, 0                        // layer masks ignored
        };

        // const int iPixelFormatAttribList[] = {
        //     WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        //     WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        //     WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        //     WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        //     WGL_COLOR_BITS_ARB, 32,
        //     WGL_DEPTH_BITS_ARB, 24,
        //     WGL_STENCIL_BITS_ARB, 8,
        //     WGL_SAMPLES_ARB, 4,
        //     0 // End of attributes list
        // };
        // int attributes[] = {
        //     WGL_CONTEXT_MAJOR_VERSION_ARB, 3
        //     , WGL_CONTEXT_MINOR_VERSION_ARB, 2
        //     , WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
        //     , 0
        // };

        static int iPixelFormat = 0;
        // UINT iNumFormats = 0;

        // 只需要执行一次
        if (iPixelFormat == 0)
        {
            // wglChoosePixelFormatARB(*hDC, iPixelFormatAttribList, NULL, 1, &iPixelFormat, (UINT*)&iNumFormats);
            // SuiDialog$MessageDialog_alert("pixform", "sdlkfj");
            iPixelFormat = ChoosePixelFormat(*hDC, &pfd);
        }

        auto ok = SetPixelFormat(*hDC, iPixelFormat, &pfd);
        printf("hi\n");
        // setTransparent(hWnd);
    }


//    PIXELFORMATDESCRIPTOR pfd;
//    HGLRC prc, rc;
//    HDC pdc, dc;
//    ZeroMemory(&pfd, sizeof(pfd));
//    pfd.nSize = sizeof(pfd);
//    pfd.nVersion = 1;
//    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
//    pfd.iPixelType = PFD_TYPE_RGBA;
//    pfd.cColorBits = 24;

//    dc = GetDC(hWnd);
//    auto pf = ChoosePixelFormat(dc, &pfd);
//    if (!SetPixelFormat(dc, pf, &pfd))
//    {
//        printf("SetPixelFormat fail\n");
//    }


    // create and enable the render context (RC)
    // if (!g_hrc) {
    if (sharehrc == NULL){ 
        sharehrc = *hRC = wglCreateContext(*hDC);
    } else {
        // *hRC = wglCreateContext(*hDC);
        //共享
        // wglShareLists(sharehrc, *hRC);
        *hRC = sharehrc;
    }
    //*hRC = wglCreateContextAttribsARB(*hDC, 0, attributes);

    /* g_hrc = *hRC;
 }
 else {
     *hRC = g_hrc;
 }*/
    wglMakeCurrent(*hDC, *hRC);

    static bool _glewIniting = true;
    if (_glewIniting)
    {
        _glewIniting = false;

        GLenum ok = glewInit();
        GLenum glok = GLEW_OK;
        printf("glewInit:ok:%d == %d\n", ok, glok);

        int multisampleSupportted = glewIsExtensionSupported("WGL_ARB_multisample");
        printf("support msaa:%d\n", multisampleSupportted);

        // wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");
        {
            int ok = wglSwapIntervalEXT(0);
            printf("set SwapInterval:%d\n", ok);
        }
    }
}
//static void pollMessage()
//{
//
//    MSG msg;
//    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
//    {
//        TranslateMessage(&msg);
//        DispatchMessage(&msg);
//    }
//}
//static void loopEvent()
//{
//    while (true)
//    {
//        HWND hasWin = FindWindowA(CLASS_NAME, NULL);
//
//        if (!hasWin)
//        {
//            printf("no window opened\n");
//            break;
//        }
//        /* bool ok = IsWindowEnabled(hasWin);
//         printf("ok:%d\n", ok);*/
//        pollMessage();
//        Sleep(5);
//    }
//}
//void Sui$testWindow();
//void testWindow()
//{
//
//    // Sui$Window *win = Sui$Window_new();
//    URGC_VAR(Sui$Window *, win, Sui$Window_new());
//
//    win->initData(win);
//
//    //Sui$testWindow();
//
//    win->show(win);
//
//    win->setTitle(win, "你好");
//
//    URGC_VAR_CLEANUP char *refTitle = NULL;
//    win->getTitle(&refTitle, win);
//    printf("已设置的  标题为:%s\n", refTitle);
//
//    win->setPos(win, 400, 200);
//    win->setSize(win, 400, 400);
//
//    win->layoutAndDraw(win);
//
//    {
//
//        URGC_VAR_CLEANUP SuiCore$Vec2 *pos = NULL;
//        win->getPos(&pos, win);
//        URGC_VAR_CLEANUP SuiCore$Vec2 *size = NULL;
//        win->getSize(&size, win);
//        URGC_VAR_CLEANUP SuiCore$Vec2 *clientSize = NULL;
//        win->getClientSize(&clientSize, win);
//        URGC_VAR_CLEANUP SuiCore$Inset *nc = NULL;
//        win->getNonClientInset(&nc, win);
//
//        printf("已设置的pos为:%f,%f, size:%f,%f, client:%f,%f, nc:%f,%f,%f,%f\n", pos->x, pos->y, size->x, size->y, clientSize->x, clientSize->y, nc->left, nc->top, nc->right, nc->bottom);
//    }
//
//
//    loopEvent();
//    // orc_delete(win);
//}
//void WindowWin32$create()
//{
//    _init();
//
//    printf("lala\n");
//    printf("s\n");
//    printf("s\n");
//    printf("WindowWin232create    \n");
//
//    HWND hwnd = _createWindow();
//    HDC hdc = NULL;
//    HGLRC hrc = NULL;
//    _enable_opengl(hwnd, &hdc, &hrc);
//
//    // setPixelFormat(hwnd);
//
//    // HGLRC temphRC = wglCreateContext(GetDC(hwnd));  //创建一个临时的环境为了初始化glew
//    // wglMakeCurrent(GetDC(hwnd), temphRC);
//
//    NVGcontext *vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
//
//    showWindow(hwnd);
//
//    draw(hwnd, vg);
//
//    loopEvent();
//}

static WindowDataWin32 *getData(Sui$Window *self)
{
    WindowDataWin32 *ret = (WindowDataWin32 *)self->data;
    if (!ret)
    {
        printf("WindowDataWin32不存在\n");
    }
    return ret;
}

void Sui$Window$cleanData(Sui$Window *self)
{
    if (!self->data)
    {
        return;
    }
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        printf("  清理win  32data\n");
        if (data->hrc){
            //目前采用共用同一个hglrc和NVGcontext, 所以窗口释放时，不能释放hglrc
            // wglDeleteContext(data->hrc);
            data->hrc = NULL;
        }
        if (data->hwnd)
        {
            if (data->hdc){
                ReleaseDC(data->hwnd, data->hdc);
                data->hdc = NULL;
            }

            DestroyWindow(data->hwnd);
            data->hwnd = NULL;
        }
        free(data);
        self->data = NULL;
    }
}

void Sui$Window$initData(Sui$Window *self)
{
    Sui$Window$cleanData(self);

    WindowDataWin32 *data = (WindowDataWin32*)calloc(1, sizeof(WindowDataWin32));

    _init();

    HWND hwnd = _createWindow();
    SetProp(hwnd, "Sui$Window", self);


    HDC hdc = NULL;
    HGLRC hrc = NULL;
    _enable_opengl(hwnd, &hdc, &hrc);



//    ShowWindow(hwnd, SW_NORMAL);
//    UpdateWindow(hwnd);


    self->id = (long long)hwnd;

    // NVGcontext* vg = ;
    // NVGcontext *vg = nvgCreateGL2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
    // static NVGcontext *gvg = NULL;

    if (SuiCore$Global_getVg()) {
        self->canvas->data = SuiCore$Global_getVg();//共用vg
    }
    else {
        self->canvas->init(self->canvas);
    }
    // if (gvg){//vg 已存在
    //     self->canvas->data = gvg;//共用vg
    // } else {
    // }
    NVGcontext *vg = (NVGcontext*)self->canvas->data;
    // gvg = vg;



    data->hwnd = hwnd;
    data->hdc = hdc;
    data->hrc = hrc;
    data->vg = vg;

    float dpiX = GetDeviceCaps(data->hdc, LOGPIXELSX);
    data->devicePixelRatio = dpiX / 96.0f;

    // int faceid = nvgCreateFont(vg, "basic", "./asset/Roboto-Regular.ttf");
    // int faceid2 = nvgCreateFont(vg, "basic", "./asset/Roboto-Bold.ttf");

    // int faceid = nvgCreateFont(vg, "basic", "./asset/msyh.ttc");
    // int faceid2 = nvgCreateFont(vg, "basic", "./asset/msyhbd.ttc");

    // int faceid = nvgCreateFont(vg, "basic", "c:\\Windows\\Fonts\\simhei.ttf");
    // int faceid = nvgCreateFont(vg, "basic", "c:\\Windows\\Fonts\\simkai.ttf");
    int faceid = nvgCreateFont(vg, "basic", "c:\\Windows\\Fonts\\msyh.ttc");
    nvgFontFace(vg, "basic");

    if (SuiCore$Global_getCanvas() == NULL){
        SuiCore$Global_setCanvas(self->canvas);
    }

    self->data = data;

    // self->draw(self);
}

void Sui$Window$setTransparent(Sui$Window* self){
    WindowDataWin32 *data = getData(self);
    if (data) {
        setTransparent(data->hwnd);
    }
}
bool Sui$Window$isVisible(Sui$Window *self){
    WindowDataWin32 *data = getData(self);
    if (data){
        bool r = IsWindowVisible(data->hwnd);
        return r;
    }
    return false;
}
void Sui$Window$show(Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        ShowWindow(data->hwnd, SW_SHOW);
    }
}
void Sui$Window$hide(Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        ShowWindow(data->hwnd, SW_HIDE);
    }
}
void Sui$Window$maximize(Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        ShowWindow(data->hwnd, SW_MAXIMIZE);
    }
}
void Sui$Window$minimize(Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        ShowWindow(data->hwnd, SW_MINIMIZE);
    }
}
void Sui$Window$normal(Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        ShowWindow(data->hwnd, SW_NORMAL);
    }
}

void Sui$Window$close(Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        DestroyWindow(data->hwnd);
    }
}

void Sui$Window$layout(Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        if (self->rootView)
        {

            //URGC_VAR_CLEANUP SuiCore$Vec2 *clientSize = NULL;
            SuiCore$Vec2 clientSize = self->getClientSize(self);

            SuiCore$Frame *ctx = &((SuiCore$ViewBase*)self->rootView)->frame;
            SuiCore$Frame$setTight(ctx, clientSize.x, clientSize.y);
            //ctx->setTight(ctx, clientSize.x, clientSize.y);
            self->rootView->layout(self->rootView, ctx);
        }
    }
}
void drawImage_atRect(NVGcontext *vg, int imgId, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh) {
    int imgW, imgH;
    nvgImageSize(vg, imgId, &imgW, &imgH);
    float wscale = dw / sw;
    float hscale = dh / sh;
    float imgScaleW = imgW * wscale   ;
    float imgScaleH = imgH * hscale;

    float ox = -sx * wscale + dx;
    float oy = -sy * hscale + dy;

    //创建图片笔刷。  ex,ey表示图片缩放到目标宽高
    NVGpaint paint = nvgImagePattern(vg, ox, oy, imgScaleW, imgScaleH, 0.f, 3, 1.f);
    nvgFillPaint(vg, paint);

    nvgBeginPath(vg);
    nvgRect(vg, dx, dy, dw, dh);
}


// typedef struct Vertex
// {
//     vec2 pos;
//     vec3 col;
// } Vertex;

// struct Vec3 {
//     float x;
//     float y;
//     float z;
// };

// static const Vertex vertices[3] =
// {
//     { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
//     { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
//     { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
// };
// static std::vector<Vec3> vertices2; 
// static std::vector<unsigned int> indices; 

// static const char* vertex_shader_text =
// "#version 330\n"
// "uniform mat4 MVP;\n"
// "in vec3 vCol;\n"
// "in vec3 vPos;\n"
// "out vec3 color;\n"
// "void main()\n"
// "{\n"
// "    gl_Position = MVP * vec4(vPos, 1.0);\n"
// "    color = vCol;\n"
// "}\n";

// static const char* fragment_shader_text =
// "#version 330\n"
// "in vec3 color;\n"
// "out vec4 fragment;\n"
// "void main()\n"
// "{\n"
// "    fragment = vec4(1.0, 1.0, 1.0, 1.0);\n"
// "}\n";


// Mesh
// void processMesh(aiMesh *mesh, const aiScene *scene)
// {
//     // static bool has = false;
//     // if (has){
//     //     return;
//     // }
//     // vector<Vertex> vertices;
//     // vector<unsigned int> indices;
//     // vector<Texture> textures;
//     float scale = 100.0;

//     int start = vertices2.size();

//     for(unsigned int i = 0; i < mesh->mNumVertices; i++)
//     {
//         // has = true;
//         Vec3 v3;
//         v3.x = mesh->mVertices[i].x / scale;
//         v3.y = mesh->mVertices[i].y / scale;
//         v3.z = mesh->mVertices[i].z / scale;
//         printf("\t%f,%f,%f\n", v3.x, v3.y, v3.z);
//         vertices2.push_back(v3);
//         // Vertex vertex;
//         // 处理顶点位置、法线和纹理坐标
//         // vertices.push_back(vertex);
//     }
//     // 处理索引
//     for(unsigned int i = 0; i < mesh->mNumFaces; i++)
//     {
//         aiFace face = mesh->mFaces[i];
//         for(unsigned int j = 0; j < face.mNumIndices; j++){
//             auto idx = face.mIndices[j] + start;
//             indices.push_back(idx);
//             printf("\t%d,", idx);
//         }
//         printf("\n");
//     }
//     // 处理材质
//     if(mesh->mMaterialIndex >= 0)
//     {
//     }

//     // return Mesh(vertices, indices, textures);
// }
// void processNode(aiNode* node, const aiScene * scene, int deep){

//     for (int i = 0; i < deep; i++){
//         printf("\t");
//     }
//     printf("%s meshs:%d kids:%d meta:%d\n", node->mName.C_Str(), 
//         node->mNumMeshes, node->mNumChildren,
//         node->mMetaData ?  node->mMetaData->mNumProperties
//         : 0
//     );
//     //元数据
//     if (node->mMetaData && node->mMetaData->mNumProperties > 0){
//         for (int i = 0; i < node->mMetaData->mNumProperties; i++){
//             const aiString* key = nullptr;
//             const aiMetadataEntry *entry = nullptr;

//             if (node->mMetaData->Get(i, key, entry)){
//                 for (int i = 0; i < deep + 1; i++){
//                     printf("\t");
//                 }
//                 printf("%s:", key->C_Str());
//                 void *data = entry->mData;
//                 if (entry->mType == AI_BOOL){
//                     bool *pbool = (bool*)data;
//                     printf("%s", *pbool ? "true":"false");
//                 }
//                 else if (entry->mType == AI_INT32){
//                     int *pv = (int*)data;
//                     printf("%d", *pv);
//                 }
//                 else if (entry->mType == AI_UINT64){
//                     uint64_t *pv = (uint64_t*)data;
//                     printf("%llu", *pv);
//                 }
//                 else if (entry->mType == AI_FLOAT){
//                     float *pv = (float*)data;
//                     printf("%f", *pv);
//                 }
//                 else if (entry->mType == AI_DOUBLE){
//                     double *pv = (double*)data;
//                     printf("%f", *pv);
//                 }
//                 else if (entry->mType == AI_AISTRING){
//                     aiString *pv = (aiString*)data;
//                     printf("%s", pv->C_Str());
//                 }
//                 else if (entry->mType == AI_AIVECTOR3D){
//                     aiVector3D *pv = (aiVector3D*)data;
//                     printf("Vec3(%f,%f,%f)", pv->x, pv->y, pv->z);
//                 }
//                 else if (entry->mType == AI_INT64){
//                     int64_t *pv = (int64_t*)data;
//                     printf("%lld", *pv);
//                 }
//                 else if (entry->mType == AI_UINT32){
//                     uint32_t *pv = (uint32_t*)data;
//                     printf("%u", *pv);
//                 }
//                 else {
//                     printf("meta?");
//                 }
//                 printf("\n");
//             }
//         }
//         printf("\n");
//     }
//     // 处理节点所有的网格（如果有的话）
//     for(unsigned int i = 0; i < node->mNumMeshes; i++)
//     {
//         aiMesh *mesh = scene->mMeshes[node->mMeshes[i]]; 
//         processMesh(mesh, scene);
//         // meshes.push_back();         
//     }

//     // 接下来对它的子节点重复这一过程
//     for(unsigned int i = 0; i < node->mNumChildren; i++)
//     {
//         processNode(node->mChildren[i], scene, deep+1);
//     }
// }

extern "C" void  Sgl$testDrawSgl();
extern "C" int Sgl$fboTex;
extern "C" void  Sgl$testDrawNvgImage(NVGcontext*vg){

    static int imageId = 0;
    if (imageId  == 0) {
        if (Sgl$fboTex) {
            imageId = nvglCreateImageFromHandleGL3(vg, Sgl$fboTex, 800, 600, 
                NVG_IMAGE_REPEATX|NVG_IMAGE_REPEATY
                |NVG_IMAGE_FLIPY
            );
        }
    }
    if (imageId) {
        NVGpaint paint = nvgImagePattern(vg, 
        0, 0, 400, 300, 0.f, imageId, 1.f);

        nvgFillPaint(vg, paint);
        nvgBeginPath(vg);
        nvgRect(vg, 0, 0, 800, 600);
        nvgFill(vg);
    }
}
void Sui$Window$draw(Sui$Window *self)
{
    // Sui$DragCrossWindowIndicator$_dragMove(NULL);
    // static bool inited = 0;
    // static GLuint vertex_buffer;
    // static GLuint program;
    // static GLuint vertex_array;
    // static unsigned int EBO;

    // static GLint mvp_location ;
    // static GLint vpos_location ;
    // static GLint vcol_location ;

    // static const aiScene* scene;
    // bool draw3d = false;

    // if (draw3d && !inited){
    //     inited = 1;
    //     // scene = ImportModel("C:\\ws\\oms-ts\\Sui\\assimp\\test\\models\\OBJ\\box.obj");
    //     scene = ImportModel("..\\assimp\\test\\models\\OBJ\\spider.obj");
    //     // scene = ImportModel("C:\\ws\\oms-ts\\Sui\\assimp\\test\\models\\OBJ\\spider.obj");

    //     processNode(scene->mRootNode, scene, 0);

    //     // DoTheImportThing( "C:\\ws\\oms-ts\\Sui\\assimp\\test\\models\\OBJ\\spider.obj");
    //     glGenBuffers(1, &EBO);
    //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

    //     glGenBuffers(1, &vertex_buffer);
    //     glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    //     // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    //     glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3) * vertices2.size(), vertices2.data(), GL_STATIC_DRAW);

    //     const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    //     glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    //     glCompileShader(vertex_shader);

    //     const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    //     glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    //     glCompileShader(fragment_shader);

    //     program = glCreateProgram();
    //     glAttachShader(program, vertex_shader);
    //     glAttachShader(program, fragment_shader);
    //     glLinkProgram(program);

    //     glUseProgram(program);
    //     mvp_location = glGetUniformLocation(program, "MVP");
    //     vpos_location = glGetAttribLocation(program, "vPos");
    //     vcol_location = glGetAttribLocation(program, "vCol");

    //     glGenVertexArrays(1, &vertex_array);
    //     glBindVertexArray(vertex_array);
    //     glEnableVertexAttribArray(vpos_location);
    //     // glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
    //     //                     sizeof(Vertex), (void*) offsetof(Vertex, pos));

    //     glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
    //                         sizeof(Vec3), (void*) 0);

    //     glEnableVertexAttribArray(vcol_location);
    //     glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
    //                         sizeof(Vertex), (void*) offsetof(Vertex, col));

    // }
    WindowDataWin32 *data = getData(self);
    if (data )
    {
        NVGcontext *vg = data->vg;
        HWND hwnd = data->hwnd;
        static int offset = 0;
        // offset+=1;
        RECT rect = {0};
        GetClientRect(hwnd, &rect);

        float w = rect.right - rect.left;
        float h = rect.bottom - rect.top;

        auto ok = wglMakeCurrent(data->hdc, data->hrc);
        if (!ok){
            printf("makeCurrent:%d\n", ok);
        }
        // Sgl$testDrawSgl();

        // glViewport(0, 0, w, h);
        // glClearColor(.96f, 0.96f, 0.96f, 0.f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // glViewport(0, 0, w, h);
        // glClearColor(.96f, 0.96f, 0.96f, 0.f);
        // // glClearColor(.46f, 0.06f, 0.06f, 1.f);
        // // static float red = 0.0f;
        // // red += 0.01f;
        // // glClearColor(red, 0.96f, 0.96f, 0.5f);
        // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // glEnable(GL_DEPTH_TEST);


        nvgBeginFrame(vg, w, h, data->devicePixelRatio);
        if (self->rootView)
        {
            self->rootView->draw(self->rootView, self->canvas);
        }

        // nvgFillColor(vg, nvgRGB(255, 0, 255));
        // float x = 50 + offset;
        // nvgBeginPath(vg);
        // nvgRect(vg, x, 50, 10, 10);
        // nvgFill(vg);

        // draw(data->hwnd, data->vg);
        // 
        //{

        //    nvgSave(vg);
        //    nvgTranslate(vg, 10.f, 10.f);

        //    //NVGpaint paint = nvgImagePattern(vg, 0.f, 0.f, 50.f,50.f, 0.f, 3, 1.f);
        //    //nvgFillPaint(vg, paint);


        //    //nvgBeginPath(vg);
        //    //nvgRect(vg, 20.f, 0.f, 260.f, 260.f);

        //    drawImage_atRect(vg, 3, 0.f, 10.f, 32.f, 10.f, 0.f, 0.f, 32.f, 32.f);
        //    nvgFill(vg);

        //    nvgStrokeColor(vg, nvgRGB(255, 0, 0));
        //    nvgStroke(vg);
        //    

        //    nvgRestore(vg);
        //}


        // CostUs cost;
        // {
        //     nvgFillColor(vg, nvgRGB(255, 255, 255));
        //     for (int i = 0; i < 1000; i++) {
        //         int x = rand() % 500;
        //         int y = rand() % 500;
        //         nvgText(vg, x, y, "Hello world", NULL);
        //     // canvas->drawSimpleText(text, x, y, font, paint);
        //     }
        // }
        // cost.stat("draw text");
        // cost.print("draw text");


        SuiCore$Fps$draw(&self->fps, self->canvas, h);


        // Sgl$testDrawNvgImage(vg);

        glDisable(GL_SCISSOR_TEST);
        glViewport(0, 0, w, h);
        glClearColor(.0f, 0.0f, 0.0f, 0.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        nvgEndFrame(vg);

        // Sgl$testDrawSgl();


        // if (draw3d){

        //     glViewport(0, 0, w, h);
        //     glClearColor(0.0, 0.0, 0.0, 1.0);
        //     glClear(GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        //     glEnable(GL_DEPTH_TEST);
        //     glEnable(GL_STENCIL_TEST);

        //     glEnable(GL_BLEND);
        //     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        // // glEnable(GL_CULL_FACE);
        // // glCullFace(GL_BACK);

        //     glClearDepth(1.0);
        //     // glClear(GL_COLOR_BUFFER_BIT);
        //     glClear(GL_DEPTH_BUFFER_BIT |GL_STENCIL_BUFFER_BIT);
        //     const float ratio = w / (float) h;

        //     glDisable(GL_CULL_FACE);
        //     glDisable(GL_DEPTH_TEST);
        //     glDisable(GL_SCISSOR_TEST);
        //     glDisable(GL_STENCIL_TEST);
        //     glDisable(GL_ALPHA_TEST);

        //     mat4x4 m, p, mvp;
        //     mat4x4_identity(m);
        //     static float rot = 0.f;
        //     rot+=0.01f;
        //     mat4x4_rotate_Z(m, m, (float) rot);
        //     mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
        //     mat4x4_mul(mvp, p, m);
        //     glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);


        //     glUseProgram(program);
        //     glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
        //     glEnableVertexAttribArray(vpos_location);
        //     // glEnableVertexAttribArray(vcol_location);
        //     glBindVertexArray(vertex_array);

        //     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //     glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
        //     // glDrawArrays(GL_TRIANGLES, 0, 3);
        // }
        // printf("swap offset:%d x:%f\n", offset, x);
        // long long ms0 = Orc$Time_unixMs();

        // dc必须得释放。 不然会越来越慢
        // auto dc = GetDC(hwnd);
        // long long ms1 = Orc$Time_unixMs();
        SwapBuffers(data->hdc);
        // wglMakeCurrent(NULL, NULL);
        // ReleaseDC(hwnd, dc);
        // long long ms2 = Orc$Time_unixMs();
        // printf("swap:%lld,%lld\n", ms1 - ms0, ms2 - ms1);
    }
}

void Sui$Window$setTitle(Sui$Window *self, char const *title)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        wchar_t *newwcs = new_Utf8Util_toutf16(title);
        SetWindowTextW(data->hwnd, newwcs);
        free(newwcs);
    }
}
Orc$String* Sui$Window$getTitle(Orc$String** __outRef__, Sui$Window* self){
//char *Sui$Window$getTitle(char **__outRef__, Sui$Window *self)
//{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
#define N_COUNT 1024
        wchar_t buf[N_COUNT];
        GetWindowTextW(data->hwnd, buf, N_COUNT - 1);
        
        return Orc$strByWcs(__outRef__, buf);
    }
    return NULL;
}

SuiCore$Vec2 Sui$Window$getPos(Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0);
        POINT p = { 0 };
        ClientToScreen(data->hwnd, &p);
        // RECT wr = {0};
        // GetWindowRect(data->hwnd, &wr); //含标题栏
        ret.x = p.x;
        ret.y = p.y;
        // ret.x = wr.left;
        // ret.y = wr.top;
        return ret;
        //return urgc_set_var_for_return((void **)__outRef__, ret);
    }
    return SuiCore$mkVec2(0, 0);
}

void Sui$Window$setPos(Sui$Window *self, float x, float y)
{

    WindowDataWin32 *data = getData(self);
    if (data)
    {
        // URGC_VAR_CLEANUP SuiCore$Inset* ncinset = NULL;
        // Sui$Window$getNonClientInset(&ncinset, self);

        //////此处设置是WindowSize,不是ClientSize
        // SetWindowPos(data->hwnd, NULL, x - ncinset->left, y - ncinset->top, 0, 0, SWP_NOSIZE);
        SetWindowPos(data->hwnd, NULL, x, y, 0, 0, SWP_NOSIZE);
    }
}
SuiCore$Vec2 Sui$Window$getSize(Sui$Window *self)
{

    WindowDataWin32 *data = getData(self);
    SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0);
    if (data)
    {
        // RECT cr;
        // GetClientRect(data->hwnd, &cr);//rect.left/top总是0, 相对于窗口客户区

        RECT wr = {0};
        GetWindowRect(data->hwnd, &wr);
        ret.x = wr.right - wr.left;
        ret.y = wr.bottom - wr.top;
        return ret;
        //return urgc_set_var_for_return((void **)__outRef__, ret);
    }
    return ret;
}

void Sui$Window$setSize(Sui$Window *self, float x, float y)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {
        // URGC_VAR_CLEANUP SuiCore$Inset* ncinset = NULL;
        // Sui$Window$getNonClientInset(&ncinset, self);

        ////此处设置是WindowSize,不是ClientSize
        // SetWindowPos(data->hwnd, NULL, 0, 0,
        //     x + ncinset->left + ncinset->right, y + ncinset->top + ncinset->bottom, SWP_NOMOVE);

        SetWindowPos(data->hwnd, NULL, 0, 0,
                     x, y, SWP_NOMOVE);
    }
}

void Sui$Window$setRect(Sui$Window* self, float x, float y, float w, float h) {
    WindowDataWin32* data = getData(self);
    if (data)
    {
        SetWindowPos(data->hwnd, NULL, x, y,
            w, h, 0);
    }
}

SuiCore$Vec2 Sui$Window$getClientSize(Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    SuiCore$Vec2 ret = SuiCore$mkVec2(0, 0);
    if (data)
    {

        RECT cr;
        GetClientRect(data->hwnd, &cr); // rect.left/top总是0, 相对于窗口客户区

        ret.x = cr.right - cr.left;
        ret.y = cr.bottom - cr.top;
        return ret;
        //return urgc_set_var_for_return((void **)__outRef__, ret);
    }

    return ret;
}

SuiCore$Inset Sui$Window$getNonClientInset( Sui$Window *self)
{
    WindowDataWin32 *data = getData(self);
    if (data)
    {

        POINT p = {0};
        ClientToScreen(data->hwnd, &p);
        RECT cr;
        GetClientRect(data->hwnd, &cr); // rect.left/top总是0, 相对于窗口客户区
        cr.left = p.x;
        cr.top = p.y;
        cr.right += p.x;
        cr.bottom += p.y;

        RECT wr;
        GetWindowRect(data->hwnd, &wr);
        float left = cr.left - wr.left;
        float top = cr.top - wr.top;
        float right = wr.right - cr.right;
        float bottom = wr.bottom - cr.bottom;

        URGC_VAR_CLEANUP SuiCore$Inset inset = SuiCore$mkInset0();
        inset.left = left;
        inset.top = top;
        inset.right = right;
        inset.bottom = bottom;
         
        return inset;
        //return (SuiCore$Inset*)urgc_set_var_for_return((void **)__outRef__, inset);
    }  
    return SuiCore$mkInset0();
}


void Sui$Window$enable(Sui$Window * self, bool enable){
    WindowDataWin32 *data = getData(self);
    if (data)
    { 
        EnableWindow(data->hwnd, enable);
    }
}
void Sui$Window$setOwner(Sui$Window * self, Sui$Window * ownerWindow)
{
    WindowDataWin32 *data = getData(self);
    if (data){
        //取消
        if (!ownerWindow){
            SetWindowLongPtrA(data->hwnd,
                GWLP_HWNDPARENT,
                (LONG_PTR)NULL);
            return;
        }
        WindowDataWin32 *targetData = getData(ownerWindow);
        if (data && targetData)
        {
            //拥有者窗口是实现模态窗体的核心

            // SetParent(data->hwnd, targetData->hwnd);
            // 父窗口与拥有者窗口的区别：GWL_HWNDPARENT 实际上更改的是顶级窗口的拥有者，而不是子窗口的父窗口。要更改子窗口的父窗口，应使用 SetParent 函数
            SetWindowLongPtrA(data->hwnd,
                GWLP_HWNDPARENT,
                (LONG_PTR)(targetData->hwnd));

        }
    }
}


// 设置异形窗体
static void setWindowRegion(){
    HWND hWnd;
    // 可选：设置可点击区域（通过 Region）
    HRGN region = CreateRectRgn(0, 0, 200, 200);
    //HRGN region = CreatePolygonRgn(points, num_points, WINDING);
    SetWindowRgn(hWnd, region, TRUE);
}




HIMAGELIST g_hDragImageList = nullptr;          // 拖拽图像列表


//
// 创建拖拽图像列表
//
static void _CreateDragImageList()
{
    if (g_hDragImageList)
        return; // 已存在

    // 创建图像列表，使用 32 位色深以支持 alpha 通道
    g_hDragImageList = ImageList_Create(32, 32, 
        ILC_COLOR32 
        | ILC_MASK
        , 
        1, 1);
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HICON hIcon = (HICON)LoadImage(
        NULL,                   // hInstance: NULL 表示从文件加载
        "cat.ico",            // 文件路径（宽字符字符串）
        IMAGE_ICON,             // 图像类型：图标
        32, 32,                 // 所需的宽高（系统会自动选最接近的）
        LR_LOADFROMFILE |       // 从文件加载（关键！）
        LR_DEFAULTCOLOR         // 使用彩色（非灰度）
    );

    ImageList_ReplaceIcon(g_hDragImageList, -1, hIcon);
    DestroyIcon(hIcon);
    if (1){
        return;
    }

    if (g_hDragImageList)
    {
        // 创建内存 DC 和位图
        HDC hdc = GetDC(nullptr);
        HDC hdcMem = CreateCompatibleDC(hdc);

        // 创建 32 位位图以支持透明度
        BITMAPINFO bi = {0};
        bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bi.bmiHeader.biWidth = 32;
        bi.bmiHeader.biHeight = -32; // 负值表示自上而下的位图
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;

        void* pBits = nullptr;
        HBITMAP hBitmap = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &pBits, nullptr, 0);
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

        // 清空位图为完全透明
        if (pBits)
        {
            memset(pBits, 0, 32 * 32 * 4); // 全部设为 0（透明）
        }

        // 设置透明背景模式
        SetBkMode(hdcMem, TRANSPARENT);

        // 绘制应用程序图标
        HICON hIcon = LoadIcon(nullptr, IDI_APPLICATION);
        if (hIcon)
        {
            //DrawIconEx(hdcMem, 8, 8, hIcon, 48, 48, 0, nullptr, DI_NORMAL);
        }

        // 手动绘制像素级的加号，避免任何背景色
        if (pBits)
        {
            DWORD* pixels = (DWORD*)pBits;
            DWORD greenColor = 0xFF00C800; // ARGB: Alpha=255, R=0, G=200, B=0

            // 绘制水平线 (y=52, x=45到59)
            for (int x = 13; x <= 27; x++)
            {
                for (int lineWidth = 0; lineWidth < 4; lineWidth++)
                {
                    int y = 17 + lineWidth - 2;
                    if (y >= 0 && y < 32 && x >= 0 && x < 32)
                    {
                        pixels[y * 32 + x] = greenColor;
                    }
                }
            }

            // 绘制垂直线 (x=52, y=45到59)
            for (int y = 13; y <= 27; y++)
            {
                for (int lineWidth = 0; lineWidth < 4; lineWidth++)
                {
                    int x = 17 + lineWidth - 2;
                    if (y >= 0 && y < 32 && x >= 0 && x < 32)
                    {
                        pixels[y * 32 + x] = greenColor;
                    }
                }
            }
        }

        SelectObject(hdcMem, hOldBitmap);

        // 直接添加位图到图像列表（不使用掩码，保持 alpha 通道）
        ImageList_Add(g_hDragImageList, hBitmap, nullptr);

        DeleteObject(hBitmap);
        DeleteDC(hdcMem);
        ReleaseDC(nullptr, hdc);
    }
}


//
// 销毁拖拽图像列表
//
static void _DestroyDragImageList()
{
    if (g_hDragImageList)
    {
        ImageList_Destroy(g_hDragImageList);
        g_hDragImageList = nullptr;
    }
}

void  Sui$DragCrossWindowIndicator$_start(Sui$DragCrossWindowIndicator *  self){
    _CreateDragImageList();

    // 开始拖拽图像
    ImageList_BeginDrag(g_hDragImageList, 0, 0, 0);

    // 将起始位置转换为屏幕坐标
    // POINT screenPos = startPos;
    // ClientToScreen(g_hMainWnd, &screenPos);

    POINT cursorPos;
    GetCursorPos(&cursorPos);

    // 开始在桌面上拖拽
    // ImageList_DragEnter(GetDesktopWindow(), screenPos.x, screenPos.y);
    ImageList_DragEnter(GetDesktopWindow(), cursorPos.x, cursorPos.y);

}
void  Sui$DragCrossWindowIndicator$_end(Sui$DragCrossWindowIndicator *  self){
    printf("结束 拖拽。指示器。。\n");
    // 结束拖拽图像
    ImageList_DragLeave(GetDesktopWindow());
    ImageList_EndDrag();

    _DestroyDragImageList();

}
void  Sui$DragCrossWindowIndicator$_dragMove(Sui$DragCrossWindowIndicator *  self){
    if (g_hDragImageList == NULL){
        return;
    }

    
    // 获取当前鼠标位置并更新拖拽图标位置
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    printf("DragMove:%ld,%ld\n", cursorPos.x, cursorPos.y);

    // 移动过程中
    // ImageList_DragLeave(GetDesktopWindow());  // 离开当前窗口
    // ImageList_DragMove(pt.x, pt.y);  // 移动到新位置
    // ImageList_DragShowNolock(true);
    ImageList_DragMove(cursorPos.x, cursorPos.y);
    // ImageList_DragEnter(GetDesktopWindow(), cursorPos.x, cursorPos.y);  // 重新进入


}
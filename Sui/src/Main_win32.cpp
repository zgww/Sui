
#include <Windows.h>
#include <consoleapi.h>
#include <stdio.h>
#include <winuser.h>

static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // auto win = get_window_by_hwnd(hwnd);
    void *win = NULL;
    if (1 || win)
    {
        switch (uMsg)
        {

        //case WM_LBUTTONDOWN:
        //    return _mouse_down(hwnd, 1, wParam, lParam);
            // 鼠标
            //  case WM_LBUTTONDOWN: return _mouse_down(hwnd, 1, wParam, lParam);
            //  case WM_MBUTTONDOWN: return _mouse_down(hwnd, 2, wParam, lParam);
            //  case WM_RBUTTONDOWN: return _mouse_down(hwnd, 3, wParam, lParam);
            //  case WM_LBUTTONUP: return _mouse_up(hwnd, 1, wParam, lParam);
            //  case WM_MBUTTONUP: return _mouse_up(hwnd, 2, wParam, lParam);
            //  case WM_RBUTTONUP: return _mouse_up(hwnd, 3, wParam, lParam);
            //  case WM_MOUSEMOVE: return _mouse_move(hwnd, wParam, lParam);
            // case WM_MOUSELEAVE: return _mouse_leave(win, wParam, lParam);
            //     //滚轮
            // case WM_MOUSEWHEEL: return _mouse_wheel(hwnd, wParam, lParam);
            //     //键盘
            //  case WM_KEYDOWN: return _key_down(hwnd, wParam, lParam);
            /*
            任意字符键
            BACKSPACE 退格
            ENTER（回车）
            ESC 退出
            SHIFT + ENTER（换行）
            TAB*/
            //  case WM_CHAR: return _char(hwnd, wParam, lParam);
            //  case WM_KEYUP: return _key_up(hwnd, wParam, lParam);
            //  case WM_SETFOCUS: return _set_focus(hwnd, wParam, lParam);
            //  case WM_KILLFOCUS: return _kill_focus(hwnd, wParam, lParam);

            // 输入法
        //  case WM_IME_CHAR: return _ime_char(hwnd, wParam, lParam);
        case WM_IME_STARTCOMPOSITION:
        {
            // printf("开始合成输入\n");
            // Ime::ins()->set_pos(win, { 0, 100 });
            break;
        }
        case WM_IME_ENDCOMPOSITION:
        {
            // _ime_end_composition(hwnd, wParam, lParam);
            break;
        }
        case WM_IME_COMPOSITION:
        {
            // _ime_composition(hwnd, wParam, lParam);
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
            //  return _command(hwnd, wParam, lParam);
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
            // return 0;
        }
        case WM_PAINT:
        {
            // draw(hwnd);
            printf("WM_PAINT\n");
            ValidateRect(hwnd, NULL); //清空无效区域
            // SuiCore$App_repaintWindowById((long long)hwnd);
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

            // SuiCore$App_onDestroyWindow((long long)hwnd);
            break;
        }
        }
    }
    return DefWindowProcA(hwnd, uMsg, wParam, lParam);
}
static const char *CLASS_NAME = "SuiAppWindow";
static void _registerWinClass()
{

    HINSTANCE hInstance = GetModuleHandle(0);
    // INITCOMMONCONTROLSEX cx = { sizeof(INITCOMMONCONTROLSEX), ICC_BAR_CLASSES };
    // BOOL ret = InitCommonControlsEx(&cx);

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME; // Utf8Util::toutf16(CLASS_NAME).c_str();
    // wc.style = CS_HREDRAW | CS_VREDRAW;
    WORD ok = RegisterClassA(&wc);
    printf("RegisterClass A ok:%d\n", ok);
}


static HWND _createWindow()
{

    DWORD style = 0;

    style = WS_OVERLAPPEDWINDOW
        ;// | WS_VISIBLE; //WS_VISIBLE会立即触发WM_PAINT; 初始宽高未设置好的话，就会闪烁
        // style = WS_POPUP;
    HWND hwnd = CreateWindowExA(
        0,                          // Optional window styles.
        CLASS_NAME,                 // Window class
        "Learn to Program Windows", // Window text
        style,                      // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,               // Parent window
        NULL,               // Menu
        GetModuleHandle(0), // Instance handle
        NULL                // Additional application data
    );
    return hwnd;
}
static void pollMessage()
{

   MSG msg;
   while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
   {
       TranslateMessage(&msg);
       DispatchMessage(&msg);
   }
}
static void windowLoop(){
   while (true)
   {
       HWND hasWin = FindWindowA(CLASS_NAME, NULL);

       if (!hasWin)
       {
           printf("no window opened\n");
           break;
       }
       /* bool ok = IsWindowEnabled(hasWin);
        printf("ok:%d\n", ok);*/
       pollMessage();
       Sleep(5);
   }
}

extern "C" 
void windowInit(){
    // FreeConsole();//解除ide/vscode的控制台。否则AllocConsole无效
    // AllocConsole();
    // freopen("CONOUT$", "w", stdout);
    SetConsoleOutputCP (65001);

    printf("windowInit\n");

    _registerWinClass();
    printf("windowInit end\n");

}


extern "C"
void testWindow(){
    HWND win = _createWindow();
    ShowWindow(win, SW_SHOW);
    windowLoop();
}
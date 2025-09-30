// WindowsProject1.cpp : 定义应用程序的入口点。
//
#define _CRT_SECURE_NO_WARNINGS

#include "framework.h"
#include "WindowsProject1.h"
#include <shellapi.h>
#include <string>
#include <vector>
#include <ole2.h>
#include <oleidl.h>
#include <commctrl.h>

#pragma comment(lib, "comctl32.lib")

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
std::vector<std::wstring> droppedFiles;         // 存储拖放的文件路径
bool isDragActive = false;                      // 拖拽状态标志
POINT mousePos = {0, 0};                        // 鼠标位置
HWND g_hMainWnd = nullptr;                      // 主窗口句柄
bool isInternalDragActive = false;              // 内部拖拽状态
POINT dragStartPos = {0, 0};                    // 拖拽开始位置
HIMAGELIST g_hDragImageList = nullptr;          // 拖拽图像列表

// 全局 DropTarget 实例
class CDropTarget;
extern CDropTarget* g_pDropTarget;
// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void                HandleDropFiles(HWND hWnd, HDROP hDrop);
void                CreateDragImageList();
void                DestroyDragImageList();
void                StartInternalDrag(POINT startPos);

// 拖拽源相关类的前向声明
class CDropSource;
class CDataObject;

//
// 实现 IDropTarget 接口以支持真正的拖拽检测
//
class CDropTarget : public IDropTarget
{
private:
    LONG m_refCount;

public:
    CDropTarget() : m_refCount(1) {}

    // IUnknown 方法
    STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
    {
        if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDropTarget))
        {
            *ppv = this;
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef()
    {
        return InterlockedIncrement(&m_refCount);
    }

    STDMETHODIMP_(ULONG) Release()
    {
        LONG count = InterlockedDecrement(&m_refCount);
        if (count == 0)
        {
            delete this;
        }
        return count;
    }

    // IDropTarget 方法
    STDMETHODIMP DragEnter(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
    {
        UNREFERENCED_PARAMETER(pDataObject);
        UNREFERENCED_PARAMETER(grfKeyState);

        // 拖拽进入窗口
        isDragActive = true;

        // 设置拖放效果
        *pdwEffect = DROPEFFECT_COPY;

        // 触发主窗口重绘（显示拖放状态背景）
        InvalidateRect(g_hMainWnd, nullptr, TRUE);
        UpdateWindow(g_hMainWnd);

        return S_OK;
    }

    STDMETHODIMP DragOver(DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
    {
        UNREFERENCED_PARAMETER(grfKeyState);
        UNREFERENCED_PARAMETER(pt);

        // 设置拖放效果
        *pdwEffect = DROPEFFECT_COPY;

        return S_OK;
    }

    STDMETHODIMP DragLeave()
    {
        // 拖拽离开窗口
        isDragActive = false;

        // 触发重绘
        InvalidateRect(g_hMainWnd, nullptr, TRUE);
        UpdateWindow(g_hMainWnd);

        return S_OK;
    }

    STDMETHODIMP Drop(IDataObject* pDataObject, DWORD grfKeyState, POINTL pt, DWORD* pdwEffect)
    {
        UNREFERENCED_PARAMETER(grfKeyState);
        UNREFERENCED_PARAMETER(pt);

        // 拖放完成
        isDragActive = false;

        // 从 IDataObject 中提取文件路径
        FORMATETC formatEtc = { CF_HDROP, nullptr, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
        STGMEDIUM stgMedium;

        if (SUCCEEDED(pDataObject->GetData(&formatEtc, &stgMedium)))
        {
            HDROP hDrop = (HDROP)stgMedium.hGlobal;
            HandleDropFiles(g_hMainWnd, hDrop);
            ReleaseStgMedium(&stgMedium);
        }

        *pdwEffect = DROPEFFECT_COPY;

        // 触发重绘
        InvalidateRect(g_hMainWnd, nullptr, TRUE);
        UpdateWindow(g_hMainWnd);

        return S_OK;
    }
};

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    // 初始化 OLE
    if (FAILED(OleInitialize(nullptr)))
    {
        return FALSE;
    }

    // 初始化 Common Controls
    InitCommonControls();

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        OleUninitialize();
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // 清理 OLE 拖放
    if (g_pDropTarget)
    {
        RevokeDragDrop(g_hMainWnd);
        g_pDropTarget->Release();
        g_pDropTarget = nullptr;
    }

    // 销毁拖拽图像列表
    DestroyDragImageList();

    OleUninitialize();
    return (int) msg.wParam;
}

//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   // 保存主窗口句柄
   g_hMainWnd = hWnd;

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   // 创建并注册 OLE 拖放目标
   g_pDropTarget = new CDropTarget();
   if (FAILED(RegisterDragDrop(hWnd, g_pDropTarget)))
   {
       g_pDropTarget->Release();
       g_pDropTarget = nullptr;
       return FALSE;
   }

   // 保留原有拖放功能作为备用
   DragAcceptFiles(hWnd, TRUE);

   // 创建拖拽图像列表
   CreateDragImageList();

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // 获取客户区大小
            RECT clientRect;
            GetClientRect(hWnd, &clientRect);

            // 如果正在拖拽，只显示拖放状态背景
            if (isDragActive)
            {
                // 设置背景色为浅蓝色表示可以拖放
                HBRUSH hBrush = CreateSolidBrush(RGB(200, 220, 255));
                FillRect(hdc, &clientRect, hBrush);
                DeleteObject(hBrush);

                // 绘制拖放提示文字（在窗口底部居中）
                SetBkMode(hdc, TRANSPARENT);
                SetTextColor(hdc, RGB(0, 0, 128));
                const WCHAR* dropText = L"释放以添加文件";

                RECT textRect = clientRect;
                textRect.top = clientRect.bottom - 50;
                DrawTextW(hdc, dropText, -1, &textRect, DT_CENTER | DT_TOP | DT_SINGLELINE);
            }
            else
            {
                // 正常状态，显示文件列表或提示
                if (!droppedFiles.empty())
                {
                    int y = 10;
                    for (const auto& file : droppedFiles)
                    {
                        TextOutW(hdc, 10, y, file.c_str(), (int)file.length());
                        y += 20;
                    }
                }
                else
                {
                    const WCHAR* text = L"左键拖拽开始内部拖拽\n拖放文件到此窗口";
                    RECT textRect = clientRect;
                    textRect.left = 10;
                    textRect.top = 10;
                    DrawTextW(hdc, text, -1, &textRect, DT_LEFT | DT_TOP | DT_WORDBREAK);
                }
            }

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DROPFILES:
        {
            HDROP hDrop = (HDROP)wParam;
            isDragActive = false;  // 拖拽结束
            HandleDropFiles(hWnd, hDrop);
            DragFinish(hDrop);
            InvalidateRect(hWnd, nullptr, TRUE);
        }
        break;
    case WM_LBUTTONDOWN:
        {
            // 开始内部拖拽
            POINT startPos;
            startPos.x = LOWORD(lParam);
            startPos.y = HIWORD(lParam);

            StartInternalDrag(startPos);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// "关于"框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

//
// 函数: HandleDropFiles(HWND, HDROP)
//
// 目标: 处理拖放文件事件
//
void HandleDropFiles(HWND hWnd, HDROP hDrop)
{
    // 清空之前的文件列表
    droppedFiles.clear();

    // 获取拖放文件的数量
    UINT fileCount = DragQueryFileW(hDrop, 0xFFFFFFFF, nullptr, 0);

    // 遍历所有拖放的文件
    for (UINT i = 0; i < fileCount; i++)
    {
        // 获取文件路径长度
        UINT pathLength = DragQueryFileW(hDrop, i, nullptr, 0);

        if (pathLength > 0)
        {
            // 分配缓冲区并获取文件路径
            std::wstring filePath(pathLength, L'\0');
            DragQueryFileW(hDrop, i, &filePath[0], pathLength + 1);

            // 添加到文件列表
            droppedFiles.push_back(filePath);
        }
    }

    // 在控制台输出拖放的文件（用于调试）
    for (const auto& file : droppedFiles)
    {
        OutputDebugStringW(L"拖放文件: ");
        OutputDebugStringW(file.c_str());
        OutputDebugStringW(L"\n");
    }
}

// 全局 DropTarget 实例
CDropTarget* g_pDropTarget = nullptr;

//
// 创建拖拽图像列表
//
void CreateDragImageList()
{
    if (g_hDragImageList)
        return; // 已存在

    // 创建图像列表，使用 32 位色深以支持 alpha 通道
    g_hDragImageList = ImageList_Create(64, 64, ILC_COLOR32 | ILC_MASK, 1, 1);
    HINSTANCE hInstance = GetModuleHandle(NULL);
    HICON hIcon = (HICON)LoadImage(
        NULL,                   // hInstance: NULL 表示从文件加载
        L"D:\\ws\\Sui\\Sui\\DemoProject\\cat.ico",            // 文件路径（宽字符字符串）
        IMAGE_ICON,             // 图像类型：图标
        32, 32,                 // 所需的宽高（系统会自动选最接近的）
        LR_LOADFROMFILE |       // 从文件加载（关键！）
        LR_DEFAULTCOLOR         // 使用彩色（非灰度）
    );

    ImageList_ReplaceIcon(g_hDragImageList, -1, hIcon);
    if (1) {
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
        bi.bmiHeader.biWidth = 64;
        bi.bmiHeader.biHeight = -64; // 负值表示自上而下的位图
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;

        void* pBits = nullptr;
        HBITMAP hBitmap = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &pBits, nullptr, 0);
        HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

        // 清空位图为完全透明
        if (pBits)
        {
            memset(pBits, 0, 64 * 64 * 4); // 全部设为 0（透明）
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
            for (int x = 45; x <= 59; x++)
            {
                for (int lineWidth = 0; lineWidth < 4; lineWidth++)
                {
                    int y = 52 + lineWidth - 2;
                    if (y >= 0 && y < 64 && x >= 0 && x < 64)
                    {
                        pixels[y * 64 + x] = greenColor;
                    }
                }
            }

            // 绘制垂直线 (x=52, y=45到59)
            for (int y = 45; y <= 59; y++)
            {
                for (int lineWidth = 0; lineWidth < 4; lineWidth++)
                {
                    int x = 52 + lineWidth - 2;
                    if (y >= 0 && y < 64 && x >= 0 && x < 64)
                    {
                        pixels[y * 64 + x] = greenColor;
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
void DestroyDragImageList()
{
    if (g_hDragImageList)
    {
        ImageList_Destroy(g_hDragImageList);
        g_hDragImageList = nullptr;
    }
}

//
// 实现 IDropSource 接口以支持拖拽源
//
class CDropSource : public IDropSource
{
private:
    LONG m_refCount;

public:
    CDropSource() : m_refCount(1) {}

    // IUnknown 方法
    STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
    {
        if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDropSource))
        {
            *ppv = this;
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef()
    {
        return InterlockedIncrement(&m_refCount);
    }

    STDMETHODIMP_(ULONG) Release()
    {
        LONG count = InterlockedDecrement(&m_refCount);
        if (count == 0)
        {
            delete this;
        }
        return count;
    }

    // IDropSource 方法
    STDMETHODIMP QueryContinueDrag(BOOL fEscapePressed, DWORD grfKeyState)
    {
        // 如果按下了 ESC 键，取消拖拽
        if (fEscapePressed)
        {
            return DRAGDROP_S_CANCEL;
        }

        // 如果鼠标左键被释放，完成拖拽
        if (!(grfKeyState & MK_LBUTTON))
        {
            return DRAGDROP_S_DROP;
        }

        // 继续拖拽
        return S_OK;
    }

    STDMETHODIMP GiveFeedback(DWORD dwEffect)
    {
        UNREFERENCED_PARAMETER(dwEffect);

        // 获取当前鼠标位置并直接更新拖拽图标位置
        POINT cursorPos;
        GetCursorPos(&cursorPos);
        ImageList_DragMove(cursorPos.x, cursorPos.y);
        static int i = 0;
        i++;
        printf("GiveFeedback :%d\n", i);

        // 返回 S_OK 表示我们处理了反馈，不使用默认光标
        return S_OK;
    }
};

//
// 实现 IDataObject 接口以提供拖拽数据
//
class CDataObject : public IDataObject
{
private:
    LONG m_refCount;
    std::wstring m_data;

public:
    CDataObject(const std::wstring& data) : m_refCount(1), m_data(data) {}

    // IUnknown 方法
    STDMETHODIMP QueryInterface(REFIID riid, void** ppv)
    {
        if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IDataObject))
        {
            *ppv = this;
            AddRef();
            return S_OK;
        }
        *ppv = nullptr;
        return E_NOINTERFACE;
    }

    STDMETHODIMP_(ULONG) AddRef()
    {
        return InterlockedIncrement(&m_refCount);
    }

    STDMETHODIMP_(ULONG) Release()
    {
        LONG count = InterlockedDecrement(&m_refCount);
        if (count == 0)
        {
            delete this;
        }
        return count;
    }

    // IDataObject 方法（简化实现）
    STDMETHODIMP GetData(FORMATETC* pformatetcIn, STGMEDIUM* pmedium)
    {
        if (pformatetcIn->cfFormat == CF_UNICODETEXT)
        {
            HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, (m_data.length() + 1) * sizeof(WCHAR));
            if (hGlobal)
            {
                WCHAR* pData = (WCHAR*)GlobalLock(hGlobal);
                if (pData)
                {
                    wcscpy_s(pData, m_data.length() + 1, m_data.c_str());
                    GlobalUnlock(hGlobal);

                    pmedium->tymed = TYMED_HGLOBAL;
                    pmedium->hGlobal = hGlobal;
                    pmedium->pUnkForRelease = nullptr;
                    return S_OK;
                }
                GlobalFree(hGlobal);
            }
        }
        return DV_E_FORMATETC;
    }

    STDMETHODIMP GetDataHere(FORMATETC* pformatetc, STGMEDIUM* pmedium)
    {
        UNREFERENCED_PARAMETER(pformatetc);
        UNREFERENCED_PARAMETER(pmedium);
        return E_NOTIMPL;
    }

    STDMETHODIMP QueryGetData(FORMATETC* pformatetc)
    {
        if (pformatetc->cfFormat == CF_UNICODETEXT)
            return S_OK;
        return DV_E_FORMATETC;
    }

    STDMETHODIMP GetCanonicalFormatEtc(FORMATETC* pformatectIn, FORMATETC* pformatetcOut)
    {
        UNREFERENCED_PARAMETER(pformatectIn);
        UNREFERENCED_PARAMETER(pformatetcOut);
        return E_NOTIMPL;
    }

    STDMETHODIMP SetData(FORMATETC* pformatetc, STGMEDIUM* pmedium, BOOL fRelease)
    {
        UNREFERENCED_PARAMETER(pformatetc);
        UNREFERENCED_PARAMETER(pmedium);
        UNREFERENCED_PARAMETER(fRelease);
        return E_NOTIMPL;
    }

    STDMETHODIMP EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC** ppenumFormatEtc)
    {
        UNREFERENCED_PARAMETER(dwDirection);
        UNREFERENCED_PARAMETER(ppenumFormatEtc);
        return E_NOTIMPL;
    }

    STDMETHODIMP DAdvise(FORMATETC* pformatetc, DWORD advf, IAdviseSink* pAdvSink, DWORD* pdwConnection)
    {
        UNREFERENCED_PARAMETER(pformatetc);
        UNREFERENCED_PARAMETER(advf);
        UNREFERENCED_PARAMETER(pAdvSink);
        UNREFERENCED_PARAMETER(pdwConnection);
        return E_NOTIMPL;
    }

    STDMETHODIMP DUnadvise(DWORD dwConnection)
    {
        UNREFERENCED_PARAMETER(dwConnection);
        return E_NOTIMPL;
    }

    STDMETHODIMP EnumDAdvise(IEnumSTATDATA** ppenumAdvise)
    {
        UNREFERENCED_PARAMETER(ppenumAdvise);
        return E_NOTIMPL;
    }
};

//
// 开始内部拖拽操作
//
void StartInternalDrag(POINT startPos)
{
    if (!g_hDragImageList)
        return;

    isInternalDragActive = true;
    dragStartPos = startPos;

    // 开始拖拽图像
    ImageList_BeginDrag(g_hDragImageList, 0, 0, 0);

    // 将起始位置转换为屏幕坐标
    POINT screenPos = startPos;
    ClientToScreen(g_hMainWnd, &screenPos);

    // 开始在桌面上拖拽
    ImageList_DragEnter(
        NULL
        //GetDesktopWindow()
        , 

        screenPos.x, screenPos.y);

    // 创建拖拽数据对象
    CDataObject* pDataObject = new CDataObject(L"从窗口拖拽的数据");

    // 创建拖拽源对象
    CDropSource* pDropSource = new CDropSource();

    // 执行拖拽操作
    DWORD dwEffect = 0;
    HRESULT hr = DoDragDrop(pDataObject, pDropSource, DROPEFFECT_COPY | DROPEFFECT_MOVE, &dwEffect);

    // 结束拖拽图像
    ImageList_DragLeave(
        NULL
        //GetDesktopWindow()
        );
    ImageList_EndDrag();

    isInternalDragActive = false;

    // 清理
    pDataObject->Release();
    pDropSource->Release();

    // 输出调试信息
    if (hr == DRAGDROP_S_DROP)
    {
        OutputDebugStringW(L"拖拽成功完成\n");
    }
    else if (hr == DRAGDROP_S_CANCEL)
    {
        OutputDebugStringW(L"拖拽被取消\n");
    }
    else
    {
        WCHAR debugMsg[256];
        swprintf_s(debugMsg, L"拖拽结果: 0x%08X\n", hr);
        OutputDebugStringW(debugMsg);
    }
}
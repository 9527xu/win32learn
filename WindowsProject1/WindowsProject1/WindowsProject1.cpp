// WindowsProject1.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "WindowsProject1.h"
#include<iostream>
using namespace std;
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);//这个hPrevInstance参数我使用过了，别报警告了，仅此而已。编译器设置到最高等级（lev-4）对未用过的参数会报警告
    UNREFERENCED_PARAMETER(lpCmdLine);
    AllocConsole();//打开一个控制台
    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance,////实例句柄
        IDS_APP_TITLE,//已有的资源ID（名字）
        szTitle,////存放资源的缓存区指针
        MAX_LOADSTRING//存放资源缓存区的大小
    );
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);//将窗口注册到操作系统内核

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance,//将快捷键表格资源通过实例指针加载到窗口中
        MAKEINTRESOURCE(IDC_WINDOWSPROJECT1)//MAKEINTRESOURCE(IDC_WINDOWSPROJECT1)通过函数MAKEINTRESOURCE（）调用资源的指针，并且其参数为资源的ID号
    );//加载快捷键表

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

    wcex.style          = CS_HREDRAW | CS_VREDRAW;//窗口基本风格
    wcex.lpfnWndProc    = WndProc;//窗口消息处理函数
    //https://blog.csdn.net/cdsnwhy/article/details/47305353
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;//当前程序实例句柄
    //MAKEINTRESOURCE(IDI_WINDOWSPROJECT1),MAKEINTRESOURCE是一个资源名转换的宏,把数字转换成字符串指针,因为LoadIcon需要LPCTSTR类型的参数输入
    //详细：https://blog.csdn.net/mjlsuccess/article/details/9225897
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));//加载窗口图标
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);//默认光标，可以直接填0
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);//背景色
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);//窗口标题
    wcex.lpszClassName  = szWindowClass;//窗口类名
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));//应用程序图标

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
   //https://blog.csdn.net/lizijie7471619/article/details/51058095
   HWND hWnd = CreateWindowW(szWindowClass,//窗口类名与注册窗口名保持一致
       szTitle,//窗口标题
       WS_OVERLAPPEDWINDOW,//窗口基本风格
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,//x,y,width,height
       nullptr,//// 父窗口句柄
       nullptr,// 窗口菜单句柄
       hInstance,// 程序实例句柄
       nullptr// 创建参数
   );

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

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
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
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

// “关于”框的消息处理程序。
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

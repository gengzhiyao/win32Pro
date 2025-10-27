#include "Register.h"
#include <Windows.h>
#include <stdio.h>

extern void ChildWindow(HWND hParent, HINSTANCE hIns);

/***
* 1. 窗口类是一个包含了窗口的各种参数信息的数据结构->结构体
* 2. 每个窗口都具有窗口类，基于窗口类创建窗口
* 3. 每个窗口类都具有一个名称，使用前必须先注册到系统中
*/

/**
* 窗口类分为三种：
* 系统窗口类、应用程序全局窗口类和应用程序局部窗口类
* 系统窗口类如button, edit等，可以直接使用
* 一般使用局部窗口类，不推荐全局窗口类
*/

///更改多字符集之后，所有的字符串都按照L形式的字符串进行处理
//窗口处理函数：自定义处理消息
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}//使用Step1中所创建的窗口类wc程序就能够退出
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

//入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	///基于系统窗口类创建窗口：Button是系统已经创建好的窗口类->系统窗口类
	//HWND hWnd = CreateWindow("Button", "This is a system window class: Button", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;//申请零字节缓冲区
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Parent";//窗口类名称
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将注册的窗口类写入操作系统
	HWND hWnd = CreateWindow(L"Parent", L"This is a parent window", WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	ChildWindow(hWnd,hIns);
	//消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))//只有找到WM_QUIT才返回0
	{
		TranslateMessage(&nMsg);
		DispatchMessageW(&nMsg);
	}
	return 0;
}

//ATOM RegisterClass(CONST WNDCLASS* lpWndClass);//注册成功之后，返回一个数字标识
/*
typedef struct tagWNDCLASSW
{
	UINT        style;//窗口类风格
	WNDPROC     lpfnWndProc;//窗口处理函数
	int         cbClsExtra;//窗口类的附加数据buff的大小
	int         cbWndExtra;//窗口的附加数据buff的大小
	HINSTANCE   hInstance;//当前模块的实例句柄
	HICON       hIcon;//窗口图标句柄
	HCURSOR     hCursor;//鼠标的句柄
	HBRUSH      hbrBackground;
	LPCWSTR     lpszMenuName;//窗口菜单的资源ID字符串
	LPCWSTR     lpszClassName;//窗口类的名称
} WNDCLASSW, * PWNDCLASSW, NEAR* NPWNDCLASSW, FAR* LPWNDCLASSW;
*/

/*
HWND CreateWindowExA(
	_In_ DWORD dwExStyle,//窗口的扩展风格
	_In_opt_ LPCSTR lpClassName,//已经注册的窗口类名称
	_In_opt_ LPCSTR lpWindowName,//窗口标题栏的名字
	_In_ DWORD dwStyle,//窗口的基本风格
	_In_ int X,
	_In_ int Y,
	_In_ int nWidth,
	_In_ int nHeight,
	_In_opt_ HWND hWndParent,//父窗口的句柄
	_In_opt_ HMENU hMenu,
	_In_opt_ HINSTANCE hInstance,//应用程序实例句柄
	_In_opt_ LPVOID lpParam);
	根据窗口类的名称和句柄在系统中进行匹配查找已经注册的窗口类，
	如果找到了，就申请一块内存，将窗口的数据放入这块内存中，并返回这块内存的句柄
*/

//创建子窗口：
//1. 创建时要添加父窗口的句柄
//2. 创建风格要增加：WS_CHILD|WS_VISIBLE

void ChildWindow(HWND hParent,HINSTANCE hIns)
{
	WNDCLASS w = { 0 };
	w.cbClsExtra = 0;//申请零字节缓冲区
	w.cbWndExtra = 0;
	w.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
	w.hCursor = NULL;
	w.hIcon = NULL;
	w.hInstance = hIns;
	w.lpfnWndProc = WndProc;
	w.lpszClassName = L"ChildWin";//窗口类名称
	w.lpszMenuName = NULL;
	w.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&w);//将注册的窗口类写入操作系统
	HWND hWnd = CreateWindow(L"ChildWin", L"This is a child window", WS_CHILD | WS_VISIBLE|WS_OVERLAPPEDWINDOW, 50, 50, 100, 100, hParent, NULL, hIns, NULL);
	//ShowWindow(hWnd, SW_SHOW);
}

#include <Windows.h>
#include <stdio.h>
#include "WinBase.h"

//窗口处理函数：自定义处理消息
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

//入口函数
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;//申请零字节缓冲区
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"mainwindow";//窗口类名称
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将注册的窗口类写入操作系统
	HWND hWnd = CreateWindow(L"mainwindow", L"This is title", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//消息循环
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessageW(&nMsg);//将消息交给窗口处理函数来处理
	}
	return 0;
}

/**
* 窗口的创建过程：
* 1. 定义WinMain函数
* 2. 定义窗口处理函数
* 3. 注册窗口类（向操作系统写入一些数据）
* 4. 创建窗口
* 5. 显示窗口
* 6. 消息循环与消息处理
*/
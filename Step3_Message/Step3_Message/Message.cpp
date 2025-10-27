#pragma once
#include <Windows.h>
#include "Message.h"
#include "CreateMessage.h"

/**  win平台下消息的组成：
* 1. 窗口句柄
* 2. 消息ID
* 3. 消息的两个参数
* 4. 消息产生时间
* 5. 消息产生时鼠标的位置
*/
///当系统通知窗口工作时，就采用消息的方式派发给窗口，由其处理函数去处理（每个窗口都有自己的窗口处理函数），同时将消息的ID和消息参数传递给窗口处理函数

/// @brief 窗口处理函数
/// @param hWnd 消息组成的第一部分
/// @param msgID 消息组成的第二部分
/// @param wParam 消息组成的第三部分
/// @param lParam 消息组成的第四部分
/// @return 
LRESULT CALLBACK CustomWndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_SYSCOMMAND:
		if (wParam==SC_CLOSE)
		{
			if ([hWnd]()->int
				{
					return MessageBox(hWnd, L"是否退出", L"这是标题", MB_YESNO);
				}()==IDYES)
			{
				//退出程序
			}
			else
			{
				return 0;
			}
		}
		//return 0; 添加这句，不会进入默认的窗口处理函数，因此，不会默认抛出WM_QUIT消息
		//MessageBox(hWnd, L"提示消息", L"标题", MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//抛出WM_QUIT消息
		break;
	case WM_SIZE:
		OnSize(hWnd,lParam);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

void RigisterClassInfo(HINSTANCE hIns)
{
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;//申请零字节缓冲区
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = CustomWndProc;
	wc.lpszClassName = L"mainwindow";//窗口类名称
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将注册的窗口类写入操作系统
}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	//在入口函数中增加这个，会同时生成console
	AllocConsole();
	consoleOutPut = GetStdHandle(STD_OUTPUT_HANDLE);


	RigisterClassInfo(hIns);
	HWND hWnd = CreateWindow(L"mainwindow", L"This is title", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG nMsg = { 0 };//该结构体正好有六个成员，代表消息的六个组成部分.
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessageW(&nMsg);//nMsg->hwnd->Find Memory->WindowProcessFunction
	}
	return 0;
}

/*
GetMessage(
	LPMSG lpMsg,//将获取到的消息存放在这个结构体中
	HWND hWnd,//获取hWnd所对应的窗口的消息
	UINT wMsgFilterMin,//获取消息ID最小范围
	UINT wMsgFilterMax);//最小最大值都为0时表示：抓取全部消息
*/

/*
TranslateMessage翻译消息，注意！它只负责处理按键消息，将按键消息翻译成字符消息
内部：检查消息是否是按键的消息，若不是按键消息，不做任何处理，继续执行
*/


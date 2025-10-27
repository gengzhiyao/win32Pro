#pragma once
#include "CreateMessage.h"
#include <Windows.h>

//WM_DESTROY消息：窗口被销毁时产生，wParam和lParam都为0

//WM_SYSCOMMAND消息：点击窗口的最大化、最小化、关闭产生，wParam具体点击的位置，lParam鼠标光标的位置：LOWORD(lParam)水平位置HIWORD(lParam)垂直位置

//WM_CREATE消息：在窗口创建成功，但未显示时，wParam为0，没有用；lParam为CREATESTRUCT类型的指针，通过这个指针可以获取CreateWindowEx中的全部12个信息->(CREATESTRUCT*)lParam

//WM_SIZE消息：窗口大小发生变化，wParam：窗口大小变化的原因，LOWORD(lParam)窗口变化后宽度，HIWORD(lParam)变化后高度

//WM_PAINT消息：窗口需要绘制的时候，wParam和lParam都为0，没用

/**
* GetMessage 从系统获取消息，将消息从系统中移除，是阻塞函数，当系统无消息时，等候下一条消息
* PeekMessage 以查看的方式从系统获取消息，可以不将消息从系统中移除，当系统没消息时，返回false，继续执行后续代码
* PeekMessage(
   LPMSG lpMsg,
   HWND hWnd,
   UINT wMsgFilterMin,
   UINT wMsgFilterMax,
   UINT wRemoveMsg);
*/

void NewMessageLoop()
{
	MSG nMsg = { 0 };
	while (true)
	{
		if (PeekMessage(&nMsg,NULL,0,0,PM_NOREMOVE))
		{
			if (GetMessage(&nMsg,NULL,0,0))
			{
				TranslateMessage(&nMsg);
				DispatchMessage(&nMsg);
			}
			else
			{
				//空闲处理
			}
		}
	}
}

/**发送消息和投递消息
SendMessage->发送消息，等候消息处理的结果
PostMessage->投递消息，发出消息后立刻返回，不等消息的处理结果
*/

#define MyMessage WM_USER+100
//PostMessage(hWnd, MyMessage, 1, 2);投送自定义消息

//调用这个函数时，就会产生绘图消息
BOOL InvalidateRect(HWND hWnd, CONST RECT* rect, BOOL erase);

///绘图消息：
/**消息处理步骤：
* HDC BeginPaint(HWND,LPPAINTSTRUCT);//开始绘图，返回绘图设备的句柄
* 正式绘图
* BOOL EndPaint(HWND,CONST PAINTSTRUCT*);//结束绘图
*/
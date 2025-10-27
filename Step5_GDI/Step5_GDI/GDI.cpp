#include "GDI.h"
#include <Windows.h>
#include "resource.h"

HINSTANCE globalHins;//保存当前程序实例句柄

//画点
void PaintPixel(HDC hDC)
{
	//SetPixel(hDC, 100, 100, RGB(255, 0, 0));
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			SetPixel(hDC, i, j, RGB(255, i, j));
		}
	}
}

void PaintLine(HDC hDC)
{
	MoveToEx(hDC, 300, 50, NULL);//指定窗口的当前点，默认为(0,0)
	LineTo(hDC, 400, 50);
	LineTo(hDC, 400, 100);//按理说，这里没有使用MoveToEx函数，是不是应该从(0,0)->(300,100)绘制一条线？
	///但是结果说明，LineTo函数内部将窗口当前点移动到了(300,50)这个点.
}

void DrawRect(HDC hDC)
{
	Rectangle(hDC, 100, 300, 200, 50);
}

extern void DrawBmp(HDC);

void OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps = { 0 };
	HDC hDC = BeginPaint(hWnd, &ps);

	//PaintPixel(hDC);
	PaintLine(hDC);
	DrawRect(hDC);

	//绘图设备-画笔
	HPEN hPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	HGDIOBJ hGDIobj = SelectObject(hDC, hPen);
	//DrawSomething
	SelectObject(hDC, hGDIobj);
	DeleteObject(hPen);

	DrawBmp(hDC);

	EndPaint(hWnd, &ps);
}



LRESULT CALLBACK CustomWndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//抛出WM_QUIT消息
		break;
	case WM_PAINT:
		OnPaint(hWnd);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

void RigisterClassInfo(HINSTANCE hIns)
{
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = CustomWndProc;
	wc.lpszClassName = "mainwindow";//窗口类名称
	wc.lpszMenuName = NULL;///注册时添加菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将注册的窗口类写入操作系统
}

//HINSTANCE ->当前程序实例句柄：能够找到本进程所在的内存
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	globalHins = hIns;
	RigisterClassInfo(hIns);
	HWND hWnd = CreateWindow("mainwindow", "绘图窗口", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
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

//绘图步骤：
//创建DC->创建绘图对象（画笔，画刷等）->将绘图对象交给DC，接收其返回值->绘图完毕，把原来的东西还给DC，销毁自己的东西
//GetStockObject();向操作系统借用画刷，透明画刷

//GDI绘图对象 画笔
//画笔的作用：线的颜色，线型，粗细   HPEN CreatePen(..)
//创建画笔，送给绘图对象  HGDIOBJ SelectObject(..)
//SelectObject(..)是交换画笔函数.
//画刷和画笔的区别，画笔用来绘制线条，画刷用来填充图形
//CreateSolidBrush 实心画刷 CreateHatchBrush 纹理画刷

//位图资源
//1 LoadBitmap
//2 创建一个与当前DC相匹配的DC（内存DC）   HDC CreateCompatibleDC(hDC);返回创建好的DC句柄
//3 将位图放入匹配的DC中
//4 成像：1:1成像 BitBlt(...)  缩放成像 StretchBlt(...)

//绘制位图资源
void DrawBmp(HDC hDC)
{
	HBITMAP hbitmap= LoadBitmap(globalHins, (char*)IDB_BITMAP1);
	HDC hmemDC= CreateCompatibleDC(hDC);//创建一个内存DC，构建一个虚拟区域，将内存DC在虚拟区域中绘图
	HGDIOBJ nOldBitmap= SelectObject(hmemDC, hbitmap);//将位图数据送给内存DC，在虚拟区域中将位图绘制出来
	BitBlt(hDC, 300, 300, 48, 48, hmemDC, 0, 0, SRCCOPY);//成像
	SelectObject(hmemDC, nOldBitmap);
	DeleteObject(hbitmap);
	DeleteDC(hmemDC);
}

//DrawText(...)文本绘制，可以在矩形局域内绘制， 注意其最后一个形参。
//以前提过一个TextOut函数，但是其功能有限
//还有CreateFont(...); 
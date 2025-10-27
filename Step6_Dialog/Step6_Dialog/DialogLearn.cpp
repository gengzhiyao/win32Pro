#include "DialogLearn.h"
#include <Windows.h>
#include "resource.h"

//对话框和窗口的区别：窗口的窗口处理函数最后调用系统的默认处理函数；但对话框的机制是：先调用系统的默认处理函数，该函数去调用我们自定义的处理函数.
//对话框分类：模态和非模态对话框

//INT CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);返回TRUE时，使用自定义的对话框窗口处理函数处理；返回FALSE时，交给系统默认对话框窗口处理函数处理
//Dialog和窗口产生的消息都一致，除了窗口初始化时产生CREATE，而对话框产生WM_INITDIALOG
//创建模态对话框使用DialogBox，创建非模态对话框使用CreateDialog函数，配合ShowWindow函数显示对话框。关闭时使用DestroyWindow销毁非模态对话框，使用EndDialog销毁模态对话框

LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{ 
	case WM_SYSCOMMAND:
		if (wParam==SC_CLOSE)
		{
			//enddialog两个作用：销毁窗口和解除阻塞
			EndDialog(hWndDlg, 50); //后面是Dialog的返回值
		}
	}
	return FALSE;
}

HINSTANCE globalhIns;

void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_Modal:
	{
		int value= DialogBox(globalhIns, (char*)IDD_DIALOG1,hWnd,DlgProc);
		int x = value;
	}
	break;
	}
}

LRESULT CALLBACK CustomWndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);//抛出WM_QUIT消息
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
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
	wc.lpszMenuName = (char*)IDR_MENU1;///注册时添加菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将注册的窗口类写入操作系统
}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	globalhIns = hIns;
	RigisterClassInfo(hIns);
	HWND hWnd = CreateWindow("mainwindow", "对话框展示", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
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

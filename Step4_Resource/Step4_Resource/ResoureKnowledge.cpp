#include "ResoureKnowledge.h"
#include <Windows.h>
#include "resource.h"

//菜单分类：1. 窗口的顶层菜单 2. 弹出式菜单 3. 系统菜单（右上角图标） 是操作系统提供的
//HMENU类型表示菜单 ID表示菜单项

//.rc    ->RC.exe    ->.res  |
//							 |  ->  link  ->.exe
//.cpp   ->cl.exe    ->.obj  |

/** 菜单资源的使用
*  1. 添加菜单资源
*  2. 加载菜单资源
*    | 注册窗口类时设置菜单
*    | 创建窗口时传参设置菜单
*    | 主窗口WM_Create消息中，利用setmenu设置菜单
*/

//学习顺序：菜单资源menu   图标icon   光标crusor   字符串表string table   快捷键资源

//快捷键：添加快捷键表，增加命令ID（即：WM_COMMAND对应的快捷键）
//两个重要函数：loadaccelerators 和 translateaccelerator

///Note:注意字符串表的ID和字符串ID不一样，快捷键表ID和快捷键ID不一样，都是两种东西

//点击菜单*项*时（注意：不是菜单），会发出消息，通过WPARAM的低字节能够获取所点击的菜单项的ID
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NEWFILE:
		MessageBox(hWnd, "菜单项：新建被点击", "标题",MB_OK);
		break;
	case ID_NEW:
		MessageBox(hWnd, "按下快捷键：CTRL+M ", "标题", MB_OK);
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
	case WM_CREATE:
		//SetMenu(hWnd,LoadMenu(HINSTANCE,(char*)IDR_MENU1));
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
	/*
	case WM_SETCURSOR:
		SetCursor(LoadCursor(HINSTANCE,CRUSORNAME));
		if LOWORD(lParam)==HTCLIENT  光标位于客户区时的行为
		return 0;//添加这句代码，不执行默认处理函数，就一直是光标资源，要不然会进入默认处理函数，光标会变为注册窗口类时的光标资源！！！
	*/
	}
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

void RigisterClassInfo(HINSTANCE hIns)
{
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = LoadCursor(hIns,(char*)IDC_CURSOR1);
	wc.hIcon = LoadIcon(hIns,(char*)IDI_ICON1);
	wc.hInstance = hIns;
	wc.lpfnWndProc = CustomWndProc;
	wc.lpszClassName = "mainwindow";//窗口类名称
	wc.lpszMenuName =(char*)IDR_MENU1;///注册时添加菜单
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//将注册的窗口类写入操作系统
}

//HINSTANCE ->当前程序实例句柄：能够找到本进程所在的内存
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	RigisterClassInfo(hIns);
	///创建窗口时，通过传入倒数第三个参数设置菜单：加载菜单资源：LoadMenu(hIns,(char*)IDR_MENU1) 将该函数放入形参
	//HWND hWnd = CreateWindow("mainwindow", "This is title", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	char buf[256] = { 0 };
	LoadString(hIns, IDS_WinString, buf, 256);
	HWND hWnd = CreateWindow("mainwindow", buf, WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//加载快捷键表，获取快捷键表的句柄
	HACCEL hAccel= LoadAccelerators(hIns, (char*)IDR_ACCELERATOR1);

	MSG nMsg = { 0 };//该结构体正好有六个成员，代表消息的六个组成部分.
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &nMsg))//TranslateAccelerator能够找到对应的快捷键时返回非零值
		{
			TranslateMessage(&nMsg);
			DispatchMessageW(&nMsg);//nMsg->hwnd->Find Memory->WindowProcessFunction
		} 
	}
	return 0;
}

/**TranslateAccelerator(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg)工作原理，伪代码：
* if(lpMsh.message!=WM_KEYDOWN) return 0;
*	根据lpMsg.wParam键码值，获知哪些按键被按下
*	拿着这个按键值到快捷键表中去查找
*	if(没找到) return 0;
*		if(找到)	SendMessage(hWnd,WM_COMMAND,wParam);//wParam的低两个字节是快捷键代表的ID，高两个字节没用都为1
*			return 1;
*/
#include "DialogLearn.h"
#include <Windows.h>
#include "resource.h"

//�Ի���ʹ��ڵ����𣺴��ڵĴ��ڴ�����������ϵͳ��Ĭ�ϴ����������Ի���Ļ����ǣ��ȵ���ϵͳ��Ĭ�ϴ��������ú���ȥ���������Զ���Ĵ�����.
//�Ի�����ࣺģ̬�ͷ�ģ̬�Ի���

//INT CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);����TRUEʱ��ʹ���Զ���ĶԻ��򴰿ڴ�������������FALSEʱ������ϵͳĬ�϶Ի��򴰿ڴ���������
//Dialog�ʹ��ڲ�������Ϣ��һ�£����˴��ڳ�ʼ��ʱ����CREATE�����Ի������WM_INITDIALOG
//����ģ̬�Ի���ʹ��DialogBox��������ģ̬�Ի���ʹ��CreateDialog���������ShowWindow������ʾ�Ի��򡣹ر�ʱʹ��DestroyWindow���ٷ�ģ̬�Ի���ʹ��EndDialog����ģ̬�Ի���

LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{ 
	case WM_SYSCOMMAND:
		if (wParam==SC_CLOSE)
		{
			//enddialog�������ã����ٴ��ںͽ������
			EndDialog(hWndDlg, 50); //������Dialog�ķ���ֵ
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
		PostQuitMessage(0);//�׳�WM_QUIT��Ϣ
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
	wc.lpszClassName = "mainwindow";//����������
	wc.lpszMenuName = (char*)IDR_MENU1;///ע��ʱ��Ӳ˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//��ע��Ĵ�����д�����ϵͳ
}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	globalhIns = hIns;
	RigisterClassInfo(hIns);
	HWND hWnd = CreateWindow("mainwindow", "�Ի���չʾ", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG nMsg = { 0 };//�ýṹ��������������Ա��������Ϣ��������ɲ���.
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessageW(&nMsg);//nMsg->hwnd->Find Memory->WindowProcessFunction
	}
	return 0;
}

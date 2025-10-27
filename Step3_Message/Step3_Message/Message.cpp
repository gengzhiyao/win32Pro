#pragma once
#include <Windows.h>
#include "Message.h"
#include "CreateMessage.h"

/**  winƽ̨����Ϣ����ɣ�
* 1. ���ھ��
* 2. ��ϢID
* 3. ��Ϣ����������
* 4. ��Ϣ����ʱ��
* 5. ��Ϣ����ʱ����λ��
*/
///��ϵͳ֪ͨ���ڹ���ʱ���Ͳ�����Ϣ�ķ�ʽ�ɷ������ڣ����䴦����ȥ����ÿ�����ڶ����Լ��Ĵ��ڴ���������ͬʱ����Ϣ��ID����Ϣ�������ݸ����ڴ�����

/// @brief ���ڴ�����
/// @param hWnd ��Ϣ��ɵĵ�һ����
/// @param msgID ��Ϣ��ɵĵڶ�����
/// @param wParam ��Ϣ��ɵĵ�������
/// @param lParam ��Ϣ��ɵĵ��Ĳ���
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
					return MessageBox(hWnd, L"�Ƿ��˳�", L"���Ǳ���", MB_YESNO);
				}()==IDYES)
			{
				//�˳�����
			}
			else
			{
				return 0;
			}
		}
		//return 0; �����䣬�������Ĭ�ϵĴ��ڴ���������ˣ�����Ĭ���׳�WM_QUIT��Ϣ
		//MessageBox(hWnd, L"��ʾ��Ϣ", L"����", MB_OK);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//�׳�WM_QUIT��Ϣ
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
	wc.cbClsExtra = 0;//�������ֽڻ�����
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = CustomWndProc;
	wc.lpszClassName = L"mainwindow";//����������
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//��ע��Ĵ�����д�����ϵͳ
}

int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	//����ں����������������ͬʱ����console
	AllocConsole();
	consoleOutPut = GetStdHandle(STD_OUTPUT_HANDLE);


	RigisterClassInfo(hIns);
	HWND hWnd = CreateWindow(L"mainwindow", L"This is title", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
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

/*
GetMessage(
	LPMSG lpMsg,//����ȡ������Ϣ���������ṹ����
	HWND hWnd,//��ȡhWnd����Ӧ�Ĵ��ڵ���Ϣ
	UINT wMsgFilterMin,//��ȡ��ϢID��С��Χ
	UINT wMsgFilterMax);//��С���ֵ��Ϊ0ʱ��ʾ��ץȡȫ����Ϣ
*/

/*
TranslateMessage������Ϣ��ע�⣡��ֻ����������Ϣ����������Ϣ������ַ���Ϣ
�ڲ��������Ϣ�Ƿ��ǰ�������Ϣ�������ǰ�����Ϣ�������κδ�������ִ��
*/


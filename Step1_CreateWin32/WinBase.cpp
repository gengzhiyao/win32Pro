#include <Windows.h>
#include <stdio.h>
#include "WinBase.h"

//���ڴ��������Զ��崦����Ϣ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;//�������ֽڻ�����
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"mainwindow";//����������
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//��ע��Ĵ�����д�����ϵͳ
	HWND hWnd = CreateWindow(L"mainwindow", L"This is title", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		TranslateMessage(&nMsg);
		DispatchMessageW(&nMsg);//����Ϣ�������ڴ�����������
	}
	return 0;
}

/**
* ���ڵĴ������̣�
* 1. ����WinMain����
* 2. ���崰�ڴ�����
* 3. ע�ᴰ���ࣨ�����ϵͳд��һЩ���ݣ�
* 4. ��������
* 5. ��ʾ����
* 6. ��Ϣѭ������Ϣ����
*/
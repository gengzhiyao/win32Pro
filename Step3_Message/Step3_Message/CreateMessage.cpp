#pragma once
#include "CreateMessage.h"
#include <Windows.h>

//WM_DESTROY��Ϣ�����ڱ�����ʱ������wParam��lParam��Ϊ0

//WM_SYSCOMMAND��Ϣ��������ڵ���󻯡���С�����رղ�����wParam��������λ�ã�lParam������λ�ã�LOWORD(lParam)ˮƽλ��HIWORD(lParam)��ֱλ��

//WM_CREATE��Ϣ���ڴ��ڴ����ɹ�����δ��ʾʱ��wParamΪ0��û���ã�lParamΪCREATESTRUCT���͵�ָ�룬ͨ�����ָ����Ի�ȡCreateWindowEx�е�ȫ��12����Ϣ->(CREATESTRUCT*)lParam

//WM_SIZE��Ϣ�����ڴ�С�����仯��wParam�����ڴ�С�仯��ԭ��LOWORD(lParam)���ڱ仯���ȣ�HIWORD(lParam)�仯��߶�

//WM_PAINT��Ϣ��������Ҫ���Ƶ�ʱ��wParam��lParam��Ϊ0��û��

/**
* GetMessage ��ϵͳ��ȡ��Ϣ������Ϣ��ϵͳ���Ƴ�����������������ϵͳ����Ϣʱ���Ⱥ���һ����Ϣ
* PeekMessage �Բ鿴�ķ�ʽ��ϵͳ��ȡ��Ϣ�����Բ�����Ϣ��ϵͳ���Ƴ�����ϵͳû��Ϣʱ������false������ִ�к�������
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
				//���д���
			}
		}
	}
}

/**������Ϣ��Ͷ����Ϣ
SendMessage->������Ϣ���Ⱥ���Ϣ����Ľ��
PostMessage->Ͷ����Ϣ��������Ϣ�����̷��أ�������Ϣ�Ĵ�����
*/

#define MyMessage WM_USER+100
//PostMessage(hWnd, MyMessage, 1, 2);Ͷ���Զ�����Ϣ

//�����������ʱ���ͻ������ͼ��Ϣ
BOOL InvalidateRect(HWND hWnd, CONST RECT* rect, BOOL erase);

///��ͼ��Ϣ��
/**��Ϣ�����裺
* HDC BeginPaint(HWND,LPPAINTSTRUCT);//��ʼ��ͼ�����ػ�ͼ�豸�ľ��
* ��ʽ��ͼ
* BOOL EndPaint(HWND,CONST PAINTSTRUCT*);//������ͼ
*/
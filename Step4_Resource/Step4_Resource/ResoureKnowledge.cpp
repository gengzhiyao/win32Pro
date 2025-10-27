#include "ResoureKnowledge.h"
#include <Windows.h>
#include "resource.h"

//�˵����ࣺ1. ���ڵĶ���˵� 2. ����ʽ�˵� 3. ϵͳ�˵������Ͻ�ͼ�꣩ �ǲ���ϵͳ�ṩ��
//HMENU���ͱ�ʾ�˵� ID��ʾ�˵���

//.rc    ->RC.exe    ->.res  |
//							 |  ->  link  ->.exe
//.cpp   ->cl.exe    ->.obj  |

/** �˵���Դ��ʹ��
*  1. ��Ӳ˵���Դ
*  2. ���ز˵���Դ
*    | ע�ᴰ����ʱ���ò˵�
*    | ��������ʱ�������ò˵�
*    | ������WM_Create��Ϣ�У�����setmenu���ò˵�
*/

//ѧϰ˳�򣺲˵���Դmenu   ͼ��icon   ���crusor   �ַ�����string table   ��ݼ���Դ

//��ݼ�����ӿ�ݼ�����������ID������WM_COMMAND��Ӧ�Ŀ�ݼ���
//������Ҫ������loadaccelerators �� translateaccelerator

///Note:ע���ַ������ID���ַ���ID��һ������ݼ���ID�Ϳ�ݼ�ID��һ�����������ֶ���

//����˵�*��*ʱ��ע�⣺���ǲ˵������ᷢ����Ϣ��ͨ��WPARAM�ĵ��ֽ��ܹ���ȡ������Ĳ˵����ID
void OnCommand(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
	case ID_NEWFILE:
		MessageBox(hWnd, "�˵���½������", "����",MB_OK);
		break;
	case ID_NEW:
		MessageBox(hWnd, "���¿�ݼ���CTRL+M ", "����", MB_OK);
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
	case WM_CREATE:
		//SetMenu(hWnd,LoadMenu(HINSTANCE,(char*)IDR_MENU1));
		break;
	case WM_COMMAND:
		OnCommand(hWnd, wParam);
	/*
	case WM_SETCURSOR:
		SetCursor(LoadCursor(HINSTANCE,CRUSORNAME));
		if LOWORD(lParam)==HTCLIENT  ���λ�ڿͻ���ʱ����Ϊ
		return 0;//��������룬��ִ��Ĭ�ϴ���������һֱ�ǹ����Դ��Ҫ��Ȼ�����Ĭ�ϴ������������Ϊע�ᴰ����ʱ�Ĺ����Դ������
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
	wc.lpszClassName = "mainwindow";//����������
	wc.lpszMenuName =(char*)IDR_MENU1;///ע��ʱ��Ӳ˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//��ע��Ĵ�����д�����ϵͳ
}

//HINSTANCE ->��ǰ����ʵ��������ܹ��ҵ����������ڵ��ڴ�
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	RigisterClassInfo(hIns);
	///��������ʱ��ͨ�����뵹���������������ò˵������ز˵���Դ��LoadMenu(hIns,(char*)IDR_MENU1) ���ú��������β�
	//HWND hWnd = CreateWindow("mainwindow", "This is title", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	char buf[256] = { 0 };
	LoadString(hIns, IDS_WinString, buf, 256);
	HWND hWnd = CreateWindow("mainwindow", buf, WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	//���ؿ�ݼ�����ȡ��ݼ���ľ��
	HACCEL hAccel= LoadAccelerators(hIns, (char*)IDR_ACCELERATOR1);

	MSG nMsg = { 0 };//�ýṹ��������������Ա��������Ϣ��������ɲ���.
	while (GetMessage(&nMsg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(hWnd, hAccel, &nMsg))//TranslateAccelerator�ܹ��ҵ���Ӧ�Ŀ�ݼ�ʱ���ط���ֵ
		{
			TranslateMessage(&nMsg);
			DispatchMessageW(&nMsg);//nMsg->hwnd->Find Memory->WindowProcessFunction
		} 
	}
	return 0;
}

/**TranslateAccelerator(HWND hWnd, HACCEL hAccTable, LPMSG lpMsg)����ԭ��α���룺
* if(lpMsh.message!=WM_KEYDOWN) return 0;
*	����lpMsg.wParam����ֵ����֪��Щ����������
*	�����������ֵ����ݼ�����ȥ����
*	if(û�ҵ�) return 0;
*		if(�ҵ�)	SendMessage(hWnd,WM_COMMAND,wParam);//wParam�ĵ������ֽ��ǿ�ݼ������ID���������ֽ�û�ö�Ϊ1
*			return 1;
*/
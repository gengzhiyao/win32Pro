#include "GDI.h"
#include <Windows.h>
#include "resource.h"

HINSTANCE globalHins;//���浱ǰ����ʵ�����

//����
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
	MoveToEx(hDC, 300, 50, NULL);//ָ�����ڵĵ�ǰ�㣬Ĭ��Ϊ(0,0)
	LineTo(hDC, 400, 50);
	LineTo(hDC, 400, 100);//����˵������û��ʹ��MoveToEx�������ǲ���Ӧ�ô�(0,0)->(300,100)����һ���ߣ�
	///���ǽ��˵����LineTo�����ڲ������ڵ�ǰ���ƶ�����(300,50)�����.
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

	//��ͼ�豸-����
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
		PostQuitMessage(0);//�׳�WM_QUIT��Ϣ
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
	wc.lpszClassName = "mainwindow";//����������
	wc.lpszMenuName = NULL;///ע��ʱ��Ӳ˵�
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//��ע��Ĵ�����д�����ϵͳ
}

//HINSTANCE ->��ǰ����ʵ��������ܹ��ҵ����������ڵ��ڴ�
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	globalHins = hIns;
	RigisterClassInfo(hIns);
	HWND hWnd = CreateWindow("mainwindow", "��ͼ����", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
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

//��ͼ���裺
//����DC->������ͼ���󣨻��ʣ���ˢ�ȣ�->����ͼ���󽻸�DC�������䷵��ֵ->��ͼ��ϣ���ԭ���Ķ�������DC�������Լ��Ķ���
//GetStockObject();�����ϵͳ���û�ˢ��͸����ˢ

//GDI��ͼ���� ����
//���ʵ����ã��ߵ���ɫ�����ͣ���ϸ   HPEN CreatePen(..)
//�������ʣ��͸���ͼ����  HGDIOBJ SelectObject(..)
//SelectObject(..)�ǽ������ʺ���.
//��ˢ�ͻ��ʵ����𣬻�������������������ˢ�������ͼ��
//CreateSolidBrush ʵ�Ļ�ˢ CreateHatchBrush ����ˢ

//λͼ��Դ
//1 LoadBitmap
//2 ����һ���뵱ǰDC��ƥ���DC���ڴ�DC��   HDC CreateCompatibleDC(hDC);���ش����õ�DC���
//3 ��λͼ����ƥ���DC��
//4 ����1:1���� BitBlt(...)  ���ų��� StretchBlt(...)

//����λͼ��Դ
void DrawBmp(HDC hDC)
{
	HBITMAP hbitmap= LoadBitmap(globalHins, (char*)IDB_BITMAP1);
	HDC hmemDC= CreateCompatibleDC(hDC);//����һ���ڴ�DC������һ���������򣬽��ڴ�DC�����������л�ͼ
	HGDIOBJ nOldBitmap= SelectObject(hmemDC, hbitmap);//��λͼ�����͸��ڴ�DC�������������н�λͼ���Ƴ���
	BitBlt(hDC, 300, 300, 48, 48, hmemDC, 0, 0, SRCCOPY);//����
	SelectObject(hmemDC, nOldBitmap);
	DeleteObject(hbitmap);
	DeleteDC(hmemDC);
}

//DrawText(...)�ı����ƣ������ھ��ξ����ڻ��ƣ� ע�������һ���βΡ�
//��ǰ���һ��TextOut�����������书������
//����CreateFont(...); 
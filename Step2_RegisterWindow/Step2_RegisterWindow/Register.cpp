#include "Register.h"
#include <Windows.h>
#include <stdio.h>

extern void ChildWindow(HWND hParent, HINSTANCE hIns);

/***
* 1. ��������һ�������˴��ڵĸ��ֲ�����Ϣ�����ݽṹ->�ṹ��
* 2. ÿ�����ڶ����д����࣬���ڴ����ഴ������
* 3. ÿ�������඼����һ�����ƣ�ʹ��ǰ������ע�ᵽϵͳ��
*/

/**
* �������Ϊ���֣�
* ϵͳ�����ࡢӦ�ó���ȫ�ִ������Ӧ�ó���ֲ�������
* ϵͳ��������button, edit�ȣ�����ֱ��ʹ��
* һ��ʹ�þֲ������࣬���Ƽ�ȫ�ִ�����
*/

///���Ķ��ַ���֮�����е��ַ���������L��ʽ���ַ������д���
//���ڴ��������Զ��崦����Ϣ
LRESULT CALLBACK WndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
	switch (msgID)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}//ʹ��Step1���������Ĵ�����wc������ܹ��˳�
	return DefWindowProc(hWnd, msgID, wParam, lParam);
}

//��ں���
int CALLBACK WinMain(HINSTANCE hIns, HINSTANCE hPreIns, LPSTR lPCmdLine, int nCmdShow)
{
	///����ϵͳ�����ഴ�����ڣ�Button��ϵͳ�Ѿ������õĴ�����->ϵͳ������
	//HWND hWnd = CreateWindow("Button", "This is a system window class: Button", WS_OVERLAPPEDWINDOW, 100, 100, 500, 500, NULL, NULL, hIns, NULL);
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;//�������ֽڻ�����
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.hCursor = NULL;
	wc.hIcon = NULL;
	wc.hInstance = hIns;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"Parent";//����������
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);//��ע��Ĵ�����д�����ϵͳ
	HWND hWnd = CreateWindow(L"Parent", L"This is a parent window", WS_OVERLAPPEDWINDOW, 0, 0, 500, 500, NULL, NULL, hIns, NULL);
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	ChildWindow(hWnd,hIns);
	//��Ϣѭ��
	MSG nMsg = { 0 };
	while (GetMessage(&nMsg, NULL, 0, 0))//ֻ���ҵ�WM_QUIT�ŷ���0
	{
		TranslateMessage(&nMsg);
		DispatchMessageW(&nMsg);
	}
	return 0;
}

//ATOM RegisterClass(CONST WNDCLASS* lpWndClass);//ע��ɹ�֮�󣬷���һ�����ֱ�ʶ
/*
typedef struct tagWNDCLASSW
{
	UINT        style;//��������
	WNDPROC     lpfnWndProc;//���ڴ�����
	int         cbClsExtra;//������ĸ�������buff�Ĵ�С
	int         cbWndExtra;//���ڵĸ�������buff�Ĵ�С
	HINSTANCE   hInstance;//��ǰģ���ʵ�����
	HICON       hIcon;//����ͼ����
	HCURSOR     hCursor;//���ľ��
	HBRUSH      hbrBackground;
	LPCWSTR     lpszMenuName;//���ڲ˵�����ԴID�ַ���
	LPCWSTR     lpszClassName;//�����������
} WNDCLASSW, * PWNDCLASSW, NEAR* NPWNDCLASSW, FAR* LPWNDCLASSW;
*/

/*
HWND CreateWindowExA(
	_In_ DWORD dwExStyle,//���ڵ���չ���
	_In_opt_ LPCSTR lpClassName,//�Ѿ�ע��Ĵ���������
	_In_opt_ LPCSTR lpWindowName,//���ڱ�����������
	_In_ DWORD dwStyle,//���ڵĻ������
	_In_ int X,
	_In_ int Y,
	_In_ int nWidth,
	_In_ int nHeight,
	_In_opt_ HWND hWndParent,//�����ڵľ��
	_In_opt_ HMENU hMenu,
	_In_opt_ HINSTANCE hInstance,//Ӧ�ó���ʵ�����
	_In_opt_ LPVOID lpParam);
	���ݴ���������ƺ;����ϵͳ�н���ƥ������Ѿ�ע��Ĵ����࣬
	����ҵ��ˣ�������һ���ڴ棬�����ڵ����ݷ�������ڴ��У�����������ڴ�ľ��
*/

//�����Ӵ��ڣ�
//1. ����ʱҪ��Ӹ����ڵľ��
//2. �������Ҫ���ӣ�WS_CHILD|WS_VISIBLE

void ChildWindow(HWND hParent,HINSTANCE hIns)
{
	WNDCLASS w = { 0 };
	w.cbClsExtra = 0;//�������ֽڻ�����
	w.cbWndExtra = 0;
	w.hbrBackground = (HBRUSH)(COLOR_WINDOW + 3);
	w.hCursor = NULL;
	w.hIcon = NULL;
	w.hInstance = hIns;
	w.lpfnWndProc = WndProc;
	w.lpszClassName = L"ChildWin";//����������
	w.lpszMenuName = NULL;
	w.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&w);//��ע��Ĵ�����д�����ϵͳ
	HWND hWnd = CreateWindow(L"ChildWin", L"This is a child window", WS_CHILD | WS_VISIBLE|WS_OVERLAPPEDWINDOW, 50, 50, 100, 100, hParent, NULL, hIns, NULL);
	//ShowWindow(hWnd, SW_SHOW);
}

#pragma once
#include <stdio.h>
//���ںͿ���̨һ�������
HANDLE consoleOutPut = 0;//���ձ�׼������

void OnSize(HWND hWnd, LPARAM lParam)
{
	short width = LOWORD(lParam);
	short height = HIWORD(lParam);

	char text[256] = { 0 };
	sprintf_s(text,"��ȣ�%d\t���߶ȣ�%d\t", width, height);
	WriteConsole(consoleOutPut, text, strlen(text), NULL, NULL);
}


#pragma once
#include <stdio.h>
//窗口和控制台一块输出：
HANDLE consoleOutPut = 0;//接收标准输出句柄

void OnSize(HWND hWnd, LPARAM lParam)
{
	short width = LOWORD(lParam);
	short height = HIWORD(lParam);

	char text[256] = { 0 };
	sprintf_s(text,"宽度：%d\t，高度：%d\t", width, height);
	WriteConsole(consoleOutPut, text, strlen(text), NULL, NULL);
}


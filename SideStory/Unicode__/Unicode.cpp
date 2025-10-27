#include "Unicode.h"
#include <Windows.h>
#include <stdio.h>

void W_char()
{
	const wchar_t* text = L"hello world";
	int len = wcslen(text);
	wprintf(L"%s, %d\n", text, len);

}

void T_char()
{
	const TCHAR* text = __TEXT("hello");
#ifdef UNICODE
	wprintf(L"%s\n", text);
#else
	printf("%s\n", text);
#endif // UNICODE

}

void Print()
{
	const wchar_t* text =L"�����ַ�̫��Ļ���wprintf��������ͻ�ʧЧ������ʹ��WriteConsole����\n";
	//��ʽ��WriteConsole(��׼������, text, wcslen(text), NULL, NULL);����ÿ�������������ǲ�֪���ģ�Ҫ��GetStdHandle��ȡ��
	HANDLE hOut= GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(hOut, text, wcslen(text), NULL, NULL);
}

int main()
{
	W_char();
	T_char();
	Print();
}
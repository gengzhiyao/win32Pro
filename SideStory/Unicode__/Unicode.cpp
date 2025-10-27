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
	const wchar_t* text =L"中文字符太多的话，wprintf这个函数就会失效。这里使用WriteConsole函数\n";
	//形式：WriteConsole(标准输出句柄, text, wcslen(text), NULL, NULL);但是每次运行输出句柄是不知道的，要用GetStdHandle获取。
	HANDLE hOut= GetStdHandle(STD_OUTPUT_HANDLE);
	WriteConsole(hOut, text, wcslen(text), NULL, NULL);
}

int main()
{
	W_char();
	T_char();
	Print();
}
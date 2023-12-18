#define _CRT_SECURE_NO_WARNINGS 1
#include "config.h"
#include "UI.h"
#include <windows.h> 
#include <tchar.h>
int b123b;
void UI() {
	SetConsoleTitle(_T("学生综合测试系统OVO"));
	system("mode con: cols=100 lines=50");
	printf("                                  学 生 综 合 测 试 系 统                                  ");
	printf("\n");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                                         功 能 1                                                  *");
	printf("*                                         功 能 2                                                  *");
	printf("*                                         功 能 3                                                  *");
	printf("*                                         功 能 4                                                  *");
	printf("*                                         功 能 5                                                  *");
	printf("*--------------------------------------------------------------------------------------------------*");
}
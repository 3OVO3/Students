#include "config.h"
#include "UI.h"
#include <tchar.h>
char flag = '0';//UI界面的标志位

//开屏显示及初始化操作
void UI_first() {
	SetConsoleTitle(_T("学生综合测试系统OVO"));//更改窗口的标题
	system("mode con: cols=100 lines=50");//更改窗口的大小为50行，100列

	//获取控制台窗口句柄
	HWND consoleWindow = GetConsoleWindow();

	// 获取屏幕尺寸
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// 获取控制台窗口的尺寸
	RECT consoleRect;
	GetWindowRect(consoleWindow, &consoleRect);
	int consoleWidth = consoleRect.right - consoleRect.left;
	int consoleHeight = consoleRect.bottom - consoleRect.top;

	// 计算窗口居中位置
	int windowX = (screenWidth - consoleWidth) / 2;
	int windowY = (screenHeight - consoleHeight) / 2;

	// 移动窗口到居中位置
	SetWindowPos(consoleWindow, 0, windowX, windowY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	//禁用最大化
	HMENU hmenu = GetSystemMenu(consoleWindow, FALSE);		// 复制或修改而访问窗口菜单
	RemoveMenu(hmenu, SC_MAXIMIZE, MF_BYCOMMAND);	// 从指定菜单删除一个菜单项或分离一个子菜单
	DrawMenuBar(consoleWindow);//重新绘制菜单栏
	
	//禁用鼠标（关闭快速编辑模式）
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);//获取控制台的句柄
	DWORD mode;
	mode &= ~ENABLE_QUICK_EDIT_MODE;//关闭快速编辑模式
	SetConsoleMode(hStdin, mode);//设置控制台的输入模式

	system("color 0C");//修改控制台内文字的颜色，浅红色
	gotoxy(38,25);//改变控制台的光标位置
	printf("欢迎来到学生综合测试系统！");
	gotoxy(0, 26);
	printf("系统启动中...");
	gotoxy(0, 27);
	for (int i = 0; i < 100; i++) {
		printf("=");
		Sleep(25);//让进程或程序进入休眠，类似于延迟函数，参数的单位为ms
	}
}

void UI_main() {
	system("cls");//清屏指令
	printf("                                       学 生 综 合 测 试 系 统                                       ");
	printf("\n");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                                                                                                  *");
	printf("*                                       1 访 问 学 生 信 息 库                                     *");
	printf("*                                                                                                  *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                                                                                                  *");
	printf("*                                       2 访 问 学 生 成 绩 库                                     *");
	printf("*                                                                                                  *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                                                                                                  *");
	printf("*                                       q 退 出 系 统                                              *");
	printf("*                                                                                                  *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("请输入对应的数字，执行功能：");
	scanf("%c", &flag);
	while ((getchar()) != '\n');//清除缓存区，直到遇到\n时才结束
	if (flag != '1' && flag != '2' && flag != 'q' && flag != 'Q') {
		flag = '0';
	}
}

void UI_students() {
	system("cls");//清屏指令
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                                  1 创 建 学 生 数 据                                             *");
	printf("*                                  2 修 改 学 生 数 据                                             *");
	printf("*                                  3 删 除 学 生 数 据                                             *");
	printf("*                                  4 浏 览 学 生 数 据                                             *");
	printf("*                                  5 查 询 学 生 数 据                                             *");
	printf("*                                  0 返 回 主 界 面                                                *");
	printf("*                                  q 退 出 系 统                                                   *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("请输入对应的数字，执行功能：");
	char student_flag;//用于接收学生信息界面的功能参数
	scanf("%c", &student_flag);
	while ((getchar()) != '\n');//清除缓存区，直到遇到\n时才结束
	if(student_flag == '0' || student_flag == 'q' || student_flag == 'Q') {
		flag = student_flag;
	}
	switch (student_flag) {
	case '1'://创建学生数据
		system("cls");//清屏指令
		create_basic();
		break;
	case '2'://修改学生数据
		system("cls");//清屏指令
		alter_basic();
		break;
	case '3'://删除学生数据
		system("cls");//清屏指令
		delete_basic();
		break;
	case '4'://浏览学生信息
		system("cls");//清屏指令
		browse_data();
		break;
	case '5'://查询学生信息
		system("cls");//清屏指令
		select_basic();
		break;
	}
}

void UI_grade() {
	system("cls");//清屏指令
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                          1 输 入 学 生 科 目 及 测 评 成 绩                                      *");
	printf("*                          2 修 改 学 生 科 目 及 测 评 成 绩                                      *");
	printf("*                          3 删 除 学 生 科 目 及 测 评 成 绩                                      *");
	printf("*                          4 浏 览 学 生 科 目 及 测 评 成 绩                                      *");
	printf("*                          5 查 询 学 生 科 目 及 测 评 成 绩                                      *");
	printf("*                          0 返 回 主 界 面                                                        *");
	printf("*                          q 退 出 系 统                                                           *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("请输入对应的数字，执行功能：");
	char grade_flag;//用于接收成绩信息界面的功能参数
	scanf("%c", &grade_flag);
	while ((getchar()) != '\n');//清除缓存区，直到遇到\n时才结束
	if (grade_flag == '0' || grade_flag == 'q' || grade_flag == 'Q') {
		flag = grade_flag;
	}
	switch (grade_flag) {
	case '1'://输入学生科目及测评成绩
		system("cls");//清屏指令
		create_grade();
		break;
	case '2'://修改学生科目及测评成绩
		system("cls");//清屏指令
		alter_grade();
		break;
	case '3'://删除学生科目及测评成绩
		system("cls");//清屏指令
		delete_grade();
		break;
	case '4'://浏览学生科目及测评成绩
		system("cls");//清屏指令
		browse_grade();
		break;
	case '5'://查询学生科目及测评成绩
		system("cls");//清屏指令
		select_grade();
		break;
	}
}

//设置控制台光标的位置
void gotoxy(short x, short y) {
	COORD coord = { x, y };//COORD是Windows API中定义的一种结构体类型，表示控制台屏幕上的坐标。以形参x和y进行初始化。
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//设置控制台光标位置
	//GetStdHandle(STD_OUTPUT_HANDLE); 获取控制台输出句柄
}

void UI() {
	UI_first();
	system("color 0A");//修改控制台内文字的颜色，浅绿色
	while (flag != -1) {
		if (flag == '0') {
			UI_main();
		}
		else if (flag == '1') {
			UI_students();
		}
		else if (flag == '2') {
			UI_grade();
		}
		else if (flag == 'q' || flag == 'Q') {
			exit(0);//关闭Dos窗口，退出程序
		}
	}
}

//color命令在控制台的用法
//COLOR[attr]
//
//attr        指定控制台输出的颜色属性。
//
//颜色属性由两个十六进制数字指定 -- 第一个
//对应于背景，第二个对应于前景。每个数字
//可以为以下任何值 :
//
//0 = 黑色       8 = 灰色
//1 = 蓝色       9 = 淡蓝色
//2 = 绿色       A = 淡绿色
//3 = 浅绿色     B = 淡浅绿色
//4 = 红色       C = 淡红色
//5 = 紫色       D = 淡紫色
//6 = 黄色       E = 淡黄色
//7 = 白色       F = 亮白色
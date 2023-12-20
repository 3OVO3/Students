#include "config.h"
#include "UI.h"
#include <tchar.h>
int flag = 0;//UI界面的标志位

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
	printf("*                                      -1 退 出 系 统                                              *");
	printf("*                                                                                                  *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("请输入对应的数字，执行功能：");
	scanf("%d", &flag);
	getchar();//吸收scanf结束时的回车符
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
	printf("*                                 -1 退 出 系 统                                                   *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("请输入对应的数字，执行功能：");
	scanf("%d", &flag);
	getchar();//吸收scanf结束时的回车符
	switch (flag) {
	case 1://创建学生数据
		system("cls");//清屏指令
		while (1) {
			create_basic();
			printf("写入成功！是否继续输入? (y or n)");
			char temp;//中间变量，接收上面的y和n
			while (1) {
				temp = getchar();
				char c;//清除缓存区用的中间变量
				while ((c = getchar()) != '\n');//清除缓存区，直到c为\n时才结束
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("请输入 y or n:");
			}
			if (temp == 'n' || temp == 'N') {//退出while循环，返回到学生信息库界面
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//继续循环，继续输入学生信息
				continue;
			}
		}
		break;
	case 2://修改学生数据
		system("cls");//清屏指令
		while (1) {
			/*     函数    */
			printf("修改成功！是否继续修改? (y or n)");
			char temp;//中间变量，接收上面的y和n
			while (1) {
				temp = getchar();
				char c;//清除缓存区用的中间变量
				while ((c = getchar()) != '\n');//清除缓存区，直到c为\n时才结束
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("请输入 y or n:");
			}
			if (temp == 'n' || temp == 'N') {//退出while循环，返回到学生信息库界面
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//继续循环，继续输入学生信息
				continue;
			}
		}
		break;
	case 3://删除学生数据
		system("cls");//清屏指令
		while (1) {
			/*     函数    */
			printf("删除成功！是否继续删除? (y or n)");
			char temp;//中间变量，接收上面的y和n
			while (1) {
				temp = getchar();
				char c;//清除缓存区用的中间变量
				while ((c = getchar()) != '\n');//清除缓存区，直到c为\n时才结束
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("请输入 y or n:");
			}
			if (temp == 'n' || temp == 'N') {//退出while循环，返回到学生信息库界面
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//继续循环，继续输入学生信息
				continue;
			}
		}
		break;
	case 4://浏览学生信息
		system("cls");//清屏指令
		/*   函数   */
		break;
	case 5://查询学生信息
		system("cls");//清屏指令
		while (1) {
			/*     函数    */
			printf("查询成功！是否继续查询? (y or n)");
			char temp;//中间变量，接收上面的y和n
			while (1) {
				temp = getchar();
				char c;//清除缓存区用的中间变量
				while ((c = getchar()) != '\n');//清除缓存区，直到c为\n时才结束
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("请输入 y or n:");
			}
			if (temp == 'n' || temp == 'N') {//退出while循环，返回到学生信息库界面
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//继续循环，继续输入学生信息
				continue;
			}
		}
		break;
	}
}

void UI_grade() {
	system("cls");//清屏指令
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                               1 输 入 学 生 科 目 成 绩                                          *");
	printf("*                               2 输 入 学 生 测 评 成 绩                                          *");
	printf("*                               0 返 回 主 界 面                                                   *");
	printf("*                              -1 退 出 系 统                                                      *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("请输入对应的数字，执行功能：");
	scanf("%d", &flag);
	getchar();//吸收scanf结束时的回车符
	switch (flag) {
	case 1:
		while (1) {
			/*    函数    */
			printf("写入成功！是否继续写入? (y or n)");
			char temp;//中间变量，接收上面的y和n
			while (1) {
				temp = getchar();
				char c;//清除缓存区用的中间变量
				while ((c = getchar()) != '\n');//清除缓存区，直到c为\n时才结束
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("请输入 y or n:");
			}
			if (temp == 'n' || temp == 'N') {//退出while循环，返回到学生信息库界面
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//继续循环，继续输入学生信息
				continue;
			}
		}
		break;
	case 2:
		while (1) {
			/*    函数    */
			printf("写入成功！是否继续输入? (y or n)");
			char temp;//中间变量，接收上面的y和n
			while (1) {
				temp = getchar();
				char c;//清除缓存区用的中间变量
				while ((c = getchar()) != '\n');//清除缓存区，直到c为\n时才结束
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("请输入 y or n:");
			}
			if (temp == 'n' || temp == 'N') {//退出while循环，返回到学生信息库界面
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//继续循环，继续输入学生信息
				continue;
			}
		}
		break;
	}
}

//设置控制台的位置
void gotoxy(short x, short y) {
	COORD coord = { x, y };//COORD是Windows API中定义的一种结构体类型，表示控制台屏幕上的坐标。以形参x和y进行初始化。
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//设置控制台光标位置
	//GetStdHandle(STD_OUTPUT_HANDLE); 获取控制台输出句柄
}

void UI() {
	SetConsoleTitle(_T("学生综合测试系统OVO"));//更改窗口的标题
	system("mode con: cols=100 lines=50");//更改窗口的大小
	while (flag != -1) {
		if (flag == 0) {
			UI_main();
		}
		else if (flag == 1) {
			UI_students();
		}
		else if (flag == 2) {
			UI_grade();
		}
		else if (flag == -1) {
			system("exit");//关闭Dos窗口，退出程序
		}
	}
}
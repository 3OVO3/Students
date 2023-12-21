#include "config.h"
#include <windows.h>
int main() {
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
    int windowX = (screenWidth-800) / 2;
    int windowY = (screenHeight-860) / 2;

    // 移动窗口到居中位置
    SetWindowPos(consoleWindow, 0, windowX, windowY, 0, 0, SWP_NOSIZE | SWP_NOZORDER);

	UI();

	//Student* p = initialize_table();
	//Student* head = p;
	//get_data(p);
	//while (1) {
	//	printf("%s %s %s %s %s\n", p->stu_num, p->stu_name, p->stu_sex, p->stu_address, p->stu_phone_num);
	//	p = p->next;
	//	if (p == head)
	//		break;
	//}
}
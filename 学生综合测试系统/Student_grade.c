#include "config.h"

//功能函数列表【5】
//创建——写学生信息的函数
void create_grade() {
	Student* head = initialize_table();
	Student* new = head;
	for (;;) {
		//若当前的学生的主科平均分排名和综测排名为0，表示当前学生是新增的，需要录入成绩
		if (new->course.rank_main_subject == 0 || new->course.rank_comprehensive == 0) {
			printf("请输入学号为%s的学生的各项成绩：\n", new->stu_num);
			for (int i = 1; i < 7; i++) {
				switch (i) {
				case 1:
					printf("请输入语文成绩：");
					scanf("%d", &new->course.mark_Chinese);
					break;
				case 2:
					printf("请输入数学成绩：");
					scanf("%d", &new->course.mark_math);
					break;
				case 3:
					printf("请输入英语成绩：");
					scanf("%d", &new->course.mark_English);
					break;
				case 4:
					printf("请输入互评分数：");
					scanf("%d", &new->course.mark_peer);
					break;
				case 5:
					printf("请输入思想品德分数：");
					scanf("%d", &new->course.mark_morality);
					break;
				case 6:
					printf("请输入教师评价分数：");
					scanf("%d", &new->course.mark_avg_Tch);
					break;
				}
			}

			//主科平均分 =（语文+数学+英语）/3
			new->course.mark_avg_main_subject = (new->course.mark_Chinese + new->course.mark_math + new->course.mark_English) / 3.0;

			//综测成绩 = 主科平均分 * 0.6 + 互评分 * 0.1 + 思想品德分数 * 0.1 + 教师评价分数 * 0.2
			//  用到了续行符：'\'
			new->course.mark_comprehensive = (new->course.mark_avg_main_subject * 0.6) + (new->course.mark_peer * 0.1) \
				+ (new->course.mark_morality * 0.1) + (new->course.mark_avg_Tch * 0.2);

			//指向下一个节点
			new = new->next;
			setbuf(stdin, NULL);//使stdin输入流由默认缓冲区转为无缓冲区,达到清除缓存区的目的
			printf("成绩录入成功");
			printf("\n\n");
			if (new == head)
				break;
		}
		else {
			new = new->next;
			if (new == head)
				break;
		}
		
	}

	renew_grade(head);
	printf("当前没有需要输入的学生成绩！");
	system("pause");
}

//修改——修改学生信息模块
void alter_grade() {
	Student* head = initialize_table();//获取链表
	Student* local = head;//记录下头文件，用local进行操纵
	char num[15];//用户输入的学号
	printf("请输入学生的学号：");
	scanf("%s", &num);//读入学号
	getchar();//清除缓存区
	for (;;) {//经过此循环，定位到学生位置
		if (strcmp(local->stu_num, num))//如果相等为0，跳出。不相等则接着遍历下一个
			local = local->next;//往下走
		else
			break;
		if (local == head) {//找不到
			printf("找不到该学生！请您重新输入！\n");
			alter_grade();
			return;//退出
		}
	}
	char choice;//选项
	int temp;//输入的要修改值

	for (;;) {
		grade_table_head_input(local);
		printf("请键入选项进行修改（a/语文成绩 b/数学成绩 c/英语成绩 d/互评分数 e/思想品德分数 f/教师评价分数 n/退出修改）：");
		scanf("%c", &choice);
		while (getchar() != '\n');//清除所有缓存区
		char choices[8] = "abcdefn";
		int bool = 0;
		for (int i = 0; i < 7; i++) {
			if (choice == choices[i])
				bool = 1;
		}
		if (bool == 0) {
			printf("您输入的选项有误，请重新输入！\n");
			continue;
		}

		if (choice == 'n')//n选项退出
			break;

		printf("请输入修改后的值：");
		scanf("%d", &temp);
		getchar();
		switch (choice)
		{
		case 'a':
			local->course.mark_Chinese = temp;
			break;
		case 'b':
			local->course.mark_math = temp;
			break;
		case 'c':
			local->course.mark_English = temp;
			break;
		case 'd':
			local->course.mark_peer = temp;
			break;
		case 'e':
			local->course.mark_morality = temp;
			break;
		case 'f':
			local->course.mark_avg_Tch = temp;
			break;
		default:
			break;
		}

		//若修改了互评分、教师评价分和思想品德分，则重新综测分
		if (choice == 'd' || choice == 'e' || choice == 'f') {
			local->course.mark_comprehensive = (local->course.mark_avg_main_subject * 0.6) + (local->course.mark_peer * 0.1) \
				+ (local->course.mark_morality * 0.1) + (local->course.mark_avg_Tch * 0.2);
		}
		//若修改了语数英的成绩，则重新计算主科平均成绩，然后重新计算综测分
		else {
			local->course.mark_avg_main_subject = (local->course.mark_Chinese + local->course.mark_math + local->course.mark_English) / 3.0;
			local->course.mark_comprehensive = (local->course.mark_avg_main_subject * 0.6) + (local->course.mark_peer * 0.1) \
				+ (local->course.mark_morality * 0.1) + (local->course.mark_avg_Tch * 0.2);
		}


		renew_grade(head);//重新写入文件

		printf("修改成功！您是否还需要继续修改？（1继续，任意键退出）");
		choice = _getch();
		if (choice != '1')
			break;
		else
			system("cls");
	}

}

//删除——删除学生信息模块
void delete_grade() {
	char num[15];//用户输入的学号
	printf("欢迎来到自助删除系统！自助删除，上不封顶，键入n退出。\n");
	printf("温馨提示：这里不删除学生的记录，只将学生的成绩信息清零，若要删除学生记录，请到学生库中操作！\n");

	for (;;) {//一次删除学生数据的过程
		Student* head = initialize_table();//获取链表
		Student* local = head;//记录下头文件，用local进行操纵
		printf("学生学号：");
		scanf("%s", &num);//读入学号
		getchar();//清除缓存区
		static int jump;//用于跳出外循环
		jump = 0;
		if (!strcmp(num, "n"))//n选项退出  
			break;
		for (;;) {//此循环用于找到学生位置的前一个
			if (strcmp(local->next->stu_num, num))//如果相等为0，跳出。不相等则接着遍历下一个
				local = local->next;//往下走
			else {
				jump = 1;
				break;
			}

			if (local == head) {//找不到 
				break;
			}
		}
		if (jump == 0) {//没找到
			printf("找不到该学生！请重新输入\n");
			continue;
		}

		//显示该学生信息
		grade_table_head_input(local->next);

		printf("请确认是否删除？ y/n ");
		char temp;
		scanf("%c", &temp);
		while (getchar() != '\n');//清除所有缓存区
		while (1) {
			if (temp == 'y' || temp == 'Y') {
				//将链表中的该学生的成绩清零
				local->next->course.mark_Chinese = 0;
				local->next->course.mark_math = 0;
				local->next->course.mark_English = 0;
				local->next->course.mark_avg_main_subject = 0;
				local->next->course.rank_main_subject = 0;
				local->next->course.mark_peer = 0;
				local->next->course.mark_morality = 0;
				local->next->course.mark_avg_Tch = 0;
				local->next->course.mark_comprehensive = 0;
				local->next->course.rank_comprehensive = 0;
				//用链表更新文件
				renew_grade(local);//此时head已经不一定在删除后的链表中了
				printf("删除成功！\n\n");
				break;
			}
			else if (temp == 'n' || temp == 'N') {
				printf("没有对%s号学生进行删除操作！\n\n", local->next->stu_num);
				break;
			}
			else {
				printf("请重新输入 y/n ！ ");
				scanf("%c", &temp);
				while (getchar() != '\n');//清除所有缓存区
			}
		}

		


		
	}
}

//查询——查询学生信息模块
void select_grade() {
	//这里寻找学号所在节点与修改函数同理
	Student* head = initialize_table();//获取链表
	Student* local = head;//记录下头文件，用local进行操纵
	char num[15];//用户输入的学号
	printf("请输入该学生的学号：");
	scanf("%s", &num);//读入学号
	getchar();//清除缓存区
	for (;;) {//经过此循环，定位到学生位置
		//printf("%s\n", local->stu_num);
		if (strcmp(local->stu_num, num))//如果相等为0，跳出。不相等则接着遍历下一个
			local = local->next;//往下走
		else
			break;
		if (local == head) {//找不到
			printf("找不到该学生！请您重新创建该学生！\n");
			system("pause");
			system("cls");//清屏
			create_basic();//创建学生函数
			system("cls");//清屏
			select_grade();
			return;//退出
		}
	}



	grade_table_head_input(local);


	printf("\n\n");
	printf("1继续查询，任意键退出：\n");
	static char c;
	c = _getch();
	if (c != '1')
		return;
	else
		select_grade();

}

//浏览学生信息
void browse_grade() {
	Student* head = initialize_table();
	Student* local = head;//保存头节点
	int col_width = 0;//列宽
	for (int i = 1;; i++) {//控制显示几行，具体行数由链表的节点数来控制
		for (int j = 1; j < 12; j++) {//显示11列

			//显示学号和姓名
			if (j == 1) {
				while (col_width < 14) {
					if (i == 1) {//第一行先输出属性名 学号
						printf(" ");
						col_width++;
						if (col_width == 5 && j == 1) {//居中显示
							col_width += printf("学号");
						}
					}
					else {
						col_width += browe_center(14, strlen(local->stu_num));
						col_width += printf("%s", local->stu_num);
						col_width += browe_center(14, strlen(local->stu_num));
					}
				}
				col_width = 0;//列宽清零
				printf("|");//作为列之间的分隔
			}

			//显示语文成绩
			else if (j == 2) {
				while (col_width < 6) {
					if (i == 1) {//第一行先输出属性名 语文
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("语文");
						}
					}
					else {
					/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(6, ((int)log10(local->course.mark_Chinese) + 1));
						col_width += printf("%d", local->course.mark_Chinese);
						col_width += browe_center(6, ((int)log10(local->course.mark_Chinese) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示数学成绩
			else if (j == 3) {
				while (col_width < 6) {
					if (i == 1) {//第一行先输出属性名 数学
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("数学");
						}
					}
					else {
					/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(6, ((int)log10(local->course.mark_math) + 1));
						col_width += printf("%d", local->course.mark_math);
						col_width += browe_center(6, ((int)log10(local->course.mark_math) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示英语成绩
			else if (j == 4) {
				while (col_width < 6) {
					if (i == 1) {//第一行先输出属性名 英语
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("英语");
						};
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(6, ((int)log10(local->course.mark_English) + 1));
						col_width += printf("%d", local->course.mark_English);
						col_width += browe_center(6, ((int)log10(local->course.mark_English) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示主科平均分
			else if (j == 5) {
				while (col_width < 12) {
					if (i == 1) {//第一行先输出属性名 主科平均分
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("主科平均分");
						}
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1+3（小数点和两位小数）就是这个浮点数的位数（包括小数点）*/
						col_width += browe_center(12, ((int)log10(local->course.mark_avg_main_subject) + 1 + 3));
						col_width += printf("%.2f", local->course.mark_avg_main_subject);
						col_width += browe_center(12, ((int)log10(local->course.mark_avg_main_subject) + 1 + 3));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示主科排名
			else if (j == 6) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 主科排名
						col_width += printf("主科排名");
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(8, ((int)log10(local->course.rank_main_subject) + 1));
						col_width += printf("%d", local->course.rank_main_subject);
						col_width += browe_center(8, ((int)log10(local->course.rank_main_subject) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示互评
			else if (j == 7) {
				while (col_width < 6) {
					if (i == 1) {//第一行先输出属性名 互评
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("互评");
						}
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(6, ((int)log10(local->course.mark_peer) + 1));
						col_width += printf("%d", local->course.mark_peer);
						col_width += browe_center(6, ((int)log10(local->course.mark_peer) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示思想品德
			else if (j == 8) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 思想品德
						col_width += printf("思想品德");
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(8, ((int)log10(local->course.mark_morality) + 1));
						col_width += printf("%d", local->course.mark_morality);
						col_width += browe_center(8, ((int)log10(local->course.mark_morality) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示教师评价
			else if (j == 9) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 教师评价
						col_width += printf("教师评价");
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(8, ((int)log10(local->course.mark_avg_Tch) + 1));
						col_width += printf("%d", local->course.mark_avg_Tch);
						col_width += browe_center(8, ((int)log10(local->course.mark_avg_Tch) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示综测分
			else if (j == 10) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 综测分
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("综测分");
						}
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1+3（小数点和两位小数）就是这个浮点数的位数（包括小数点）*/
						col_width += browe_center(8, ((int)log10(local->course.mark_comprehensive) + 1 + 3));
						col_width += printf("%.2f", local->course.mark_comprehensive);
						col_width += browe_center(8, ((int)log10(local->course.mark_comprehensive) + 1 + 3));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示综测排名
			else if (j == 11) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 综测排名
						col_width += printf("综测排名");
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(8, ((int)log10(local->course.rank_comprehensive) + 1));
						col_width += printf("%d", local->course.rank_comprehensive);
						col_width += browe_center(8, ((int)log10(local->course.rank_comprehensive) + 1));
					}
				}
				col_width = 0;//列宽清0
			}

		}

		printf("\n");
		//输出一行 "-" ，用来作为行之间的分隔
		while (col_width < 100) {
			//每次到第一行列宽（|）的位置后，改为输出一个 "+"
			if (col_width == 14 || col_width == 21 || col_width == 28 || col_width == 35 || col_width == 48 || col_width == 57 || col_width == 64 \
				|| col_width == 73 || col_width == 82 || col_width == 91) {
				printf("+");
			}
			else {
				printf("-");
			}
			col_width++;
		}
		col_width = 0;//列宽清零
		printf("\n");
		if (i > 1) {
			local = local->next;
		}
		if (local == head && i > 1) {
			break;
		}
	}
	system("pause");
}


//读写函数【1】
//更新文件——根据已有链表对csv文件进行更新
void renew_grade(Student* head) {
	head = sort_link_table(head);
	//计算学生的主科平均分排名和综测排名
	rank_main_subject(head);
	rank_comprehensive(head);
	FILE* p_ini = fopen("grade.csv", "w");
	Student* local = head;
	for (;;) {
		if (strcmp(local->stu_num, "")) {
			//写入学生学号
			fprintf(p_ini, "%s,", local->stu_num);
			//写入语文成绩
			fprintf(p_ini, "%d,", local->course.mark_Chinese);
			//写入数学成绩
			fprintf(p_ini, "%d,", local->course.mark_math);
			//写入英语成绩
			fprintf(p_ini, "%d,", local->course.mark_English);
			//写入主科平均分
			fprintf(p_ini, "%.2f,", local->course.mark_avg_main_subject);
			//写入主科排名
			fprintf(p_ini, "%d,", local->course.rank_main_subject);
			//写入互评分数
			fprintf(p_ini, "%d,", local->course.mark_peer);
			//写入思想品德分数
			fprintf(p_ini, "%d,", local->course.mark_morality);
			//写入教师评价分数
			fprintf(p_ini, "%d,", local->course.mark_avg_Tch);
			//写入综测分数
			fprintf(p_ini, "%.2f,", local->course.mark_comprehensive);
			//写入综测排名
			fprintf(p_ini, "%d\n", local->course.rank_comprehensive);
			local = local->next;
		}

		if (local == head)
			break;
	}
	fclose(p_ini);
}


//子函数列表【3】
//查询学生信息（browse_grade的副函数，仅在select_grade模块中使用，对链表指针直接进行调用，用于输出表格）
void grade_table_head_input(Student* head) {
	Student* local = head;//保存头节点
	int col_width = 0;//列宽
	for (int i = 1; i < 3; i++) {
		for (int j = 1; j < 12; j++) {//显示11列

			//显示学号和姓名
			if (j == 1) {
				while (col_width < 14) {
					if (i == 1) {//第一行先输出属性名 学号
						printf(" ");
						col_width++;
						if (col_width == 5 && j == 1) {//居中显示
							col_width += printf("学号");
						}
					}
					else {
						col_width += browe_center(14, strlen(local->stu_num));
						col_width += printf("%s", local->stu_num);
						col_width += browe_center(14, strlen(local->stu_num));
					}
				}
				col_width = 0;//列宽清零
				printf("|");//作为列之间的分隔
			}

			//显示语文成绩
			else if (j == 2) {
				while (col_width < 6) {
					if (i == 1) {//第一行先输出属性名 语文
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("语文");
						}
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(6, ((int)log10(local->course.mark_Chinese) + 1));
						col_width += printf("%d", local->course.mark_Chinese);
						col_width += browe_center(6, ((int)log10(local->course.mark_Chinese) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示数学成绩
			else if (j == 3) {
				while (col_width < 6) {
					if (i == 1) {//第一行先输出属性名 数学
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("数学");
						}
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(6, ((int)log10(local->course.mark_math) + 1));
						col_width += printf("%d", local->course.mark_math);
						col_width += browe_center(6, ((int)log10(local->course.mark_math) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示英语成绩
			else if (j == 4) {
				while (col_width < 6) {
					if (i == 1) {//第一行先输出属性名 英语
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("英语");
						};
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(6, ((int)log10(local->course.mark_English) + 1));
						col_width += printf("%d", local->course.mark_English);
						col_width += browe_center(6, ((int)log10(local->course.mark_English) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示主科平均分
			else if (j == 5) {
				while (col_width < 12) {
					if (i == 1) {//第一行先输出属性名 主科平均分
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("主科平均分");
						}
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1+3（小数点和两位小数）就是这个浮点数的位数（包括小数点）*/
						col_width += browe_center(12, ((int)log10(local->course.mark_avg_main_subject) + 1 + 3));
						col_width += printf("%.2f", local->course.mark_avg_main_subject);
						col_width += browe_center(12, ((int)log10(local->course.mark_avg_main_subject) + 1 + 3));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示主科排名
			else if (j == 6) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 主科排名
						col_width += printf("主科排名");
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(8, ((int)log10(local->course.rank_main_subject) + 1));
						col_width += printf("%d", local->course.rank_main_subject);
						col_width += browe_center(8, ((int)log10(local->course.rank_main_subject) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示互评
			else if (j == 7) {
				while (col_width < 6) {
					if (i == 1) {//第一行先输出属性名 互评
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("互评");
						}
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(6, ((int)log10(local->course.mark_peer) + 1));
						col_width += printf("%d", local->course.mark_peer);
						col_width += browe_center(6, ((int)log10(local->course.mark_peer) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示思想品德
			else if (j == 8) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 思想品德
						col_width += printf("思想品德");
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(8, ((int)log10(local->course.mark_morality) + 1));
						col_width += printf("%d", local->course.mark_morality);
						col_width += browe_center(8, ((int)log10(local->course.mark_morality) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示教师评价
			else if (j == 9) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 教师评价
						col_width += printf("教师评价");
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(8, ((int)log10(local->course.mark_avg_Tch) + 1));
						col_width += printf("%d", local->course.mark_avg_Tch);
						col_width += browe_center(8, ((int)log10(local->course.mark_avg_Tch) + 1));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示综测分
			else if (j == 10) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 综测分
						printf(" ");
						col_width++;
						if (col_width == 1) {//居中显示
							col_width += printf("综测分");
						}
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1+3（小数点和两位小数）就是这个浮点数的位数（包括小数点）*/
						col_width += browe_center(8, ((int)log10(local->course.mark_comprehensive) + 1 + 3));
						col_width += printf("%.2f", local->course.mark_comprehensive);
						col_width += browe_center(8, ((int)log10(local->course.mark_comprehensive) + 1 + 3));
					}
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示综测排名
			else if (j == 11) {
				while (col_width < 8) {
					if (i == 1) {//第一行先输出属性名 综测排名
						col_width += printf("综测排名");
					}
					else {
						/*对要显示的数取它的log10的值，然后取其结果的整数部分，最后+1就是这个整数的位数*/
						col_width += browe_center(8, ((int)log10(local->course.rank_comprehensive) + 1));
						col_width += printf("%d", local->course.rank_comprehensive);
						col_width += browe_center(8, ((int)log10(local->course.rank_comprehensive) + 1));
					}
				}
				col_width = 0;//列宽清0
			}

		}

		printf("\n");
		//输出一行 "-" ，用来作为行之间的分隔
		while (col_width < 100) {
			//每次到第一行列宽（|）的位置后，改为输出一个 "+"
			if (col_width == 14 || col_width == 21 || col_width == 28 || col_width == 35 || col_width == 48 || col_width == 57 || col_width == 64 \
				|| col_width == 73 || col_width == 82 || col_width == 91) {
				printf("+");
			}
			else {
				printf("-");
			}
			col_width++;
		}
		col_width = 0;//列宽清零
		printf("\n");
		if (i > 1) {
			local = local->next;
		}
		if (local == head && i > 1) {
			break;
		}
	}
}

//学生主科平均分排名(仅在renew_grade模块中使用)
void rank_main_subject(Student* head) {
	Student* local = head;//保存头节点，对local操作
	Student* local_later = local->next;//local_later始终表示local后面的节点，初始化为local的下一个节点
	for (;;) {
		//若当前的学生的主科平均分和综测分为0，表示当前学生没有录入成绩，不对该学生进行排名
		if (local->course.mark_avg_main_subject != 0 || local->course.mark_comprehensive != 0) {
			local->course.rank_main_subject = 1;//假设当前学生的主科排名为第一名
			while (local != local_later) {//当前学生的主科平均分排名计算流程
				//若当前学生的主科平均分小于下一个学生的主科平均分时，当前学生的主科排名加1
				if (local->course.mark_avg_main_subject < local_later->course.mark_avg_main_subject) {
					local->course.rank_main_subject++;
				}
				local_later = local_later->next;//让local_later指向下一个节点
			}
			
		}
		//当前学生结束，让local指向下个学生，local_later重新指向local的下一个学生
		local = local->next;
		local_later = local->next;
		if (local == head) {
			break;
		}
	}
}

//学生综测排名(仅在renew_grade模块中使用)
void rank_comprehensive(Student* head) {
	Student* local = head;//保存头节点，对local操作
	Student* local_later = local->next;//local_later始终表示local后面的节点，初始化为local的下一个节点
	for (;;) {
		//若当前的学生的主科平均分和综测分为0，表示当前学生没有录入成绩，不对该学生进行排名
		if (local->course.mark_avg_main_subject != 0 || local->course.mark_comprehensive != 0) {
			local->course.rank_comprehensive = 1;//假设当前学生的综测排名为第一名
			while (local != local_later) {//当前学生的主科平均分排名计算流程
				//若当前学生的综测分小于下一个学生的综测分时，当前学生的综测排名加1
				if (local->course.mark_comprehensive < local_later->course.mark_comprehensive) {
					local->course.rank_comprehensive++;
				}
				local_later = local_later->next;//让local_later指向下一个节点
			}
		
		}
		//当前学生结束，让local指向下个学生，local_later重新指向local的下一个学生
		local = local->next;
		local_later = local->next;

		if (local == head) {
			break;
		}
	}
}








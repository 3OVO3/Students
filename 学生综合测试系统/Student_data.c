#include "config.h"
#define stu_path "Student.txt"


//创建——写学生信息的函数
void create_basic() {
	FILE* p_ini = fopen("basic.csv", "r");
	if (p_ini == 0) {
		p_ini = fopen("basic.csv", "w");
	}
	else {
		fclose(p_ini);
		p_ini=fopen("basic.csv", "a");
	}

	Student *new=(Student*)malloc(sizeof(Student));

	printf("请输入学生的学号：");
	scanf("%s",new->stu_num);

	printf("请输入学生的姓名：");
	scanf("%s",new->stu_name);

	printf("请输入学生的性别：");
	scanf("%s",new->stu_sex);

	printf("请输入学生的家庭住址：");
	scanf("%s",new->stu_address);


	printf("请输入学生的联系电话：");
	scanf("%s",new->stu_phone_num);

	setbuf(stdin, NULL);//使stdin输入流由默认缓冲区转为无缓冲区,达到清除缓存区的目的
	fputs(strcat(new->stu_num, ","), p_ini);
	fputs(strcat(new->stu_name, ","), p_ini);
	fputs(strcat(new->stu_sex, ","), p_ini);
	fputs(strcat(new->stu_address, ","), p_ini);
	fputs(strcat(new->stu_phone_num, "\n"), p_ini);
	fclose(p_ini);
	Student* head;
	head=initialize_table();
	renew_data(head);
	printf("创建成功！键入1继续添加(任意键退出)：");
	if (_getch() == '1') {
		printf("\n\n");
		create_basic();
	}	
}

//修改——修改学生信息模块
void alter_basic() {
	Student* head = initialize_table();//获取链表
	Student* local = head;//记录下头文件，用local进行操纵
	char num[15];//用户输入的学号
	printf("请输入该学生的学号：");
	//如果不知道学号，可通过姓名查询学号
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
			create_basic();//创建学生函数
			return;//退出
		}
	}
	char choice;//选项
	char temp[30];//输入的要修改值
	
	for (;;) {
		printf("请键入选项进行修改（a/学号 b/姓名 c/性别 d/住址 e/联系电话 n/退出修改）：");
		scanf("%s", &choice);
		while (getchar() != '\n');//清除所有缓存区
		char choices[6] = "abcden";
		int bool=0;
		for (int i = 0; i < 6; i++) {
			if (choice == choices[i])
				bool = 1;
		}
		if (bool == 0) {
			printf("您输入的选项有误，请重新输入！\n");
			continue;
		}
		
		if (choice == 'n')//n选项退出
			break;

		printf("请输入修改后的值");
		scanf("%s", temp);
		getchar();
		switch (choice)
		{
		case 'a':
			strcpy(local->stu_num, temp);
			break;
		case 'b':
			strcpy(local->stu_name, temp);
			break;
		case 'c':
			strcpy(local->stu_sex, temp);
			break;
		case 'd':
			strcpy(local->stu_address, temp);
			break;
		case 'e':
			strcpy(local->stu_phone_num, temp);
			break;
		default:
			break;
		}
	
		
		renew_data(head);//重新写入文件

		printf("修改成功！您是否还需要继续修改？（1继续，任意键退出）");
		scanf("%c", &choice);
		getchar();
		if (choice != '1')
			break;
		else
			printf("请键入选项进行修改（a/学号 b/姓名 c/性别 d/住址 e/联系电话 n/退出修改）：");
	}
	
}
 
//删除——删除学生信息模块
void delete_basic() {
	Student* head = initialize_table();//获取链表
	Student* local = head;//记录下头文件，用local进行操纵
	char num[15];//用户输入的学号
	printf("欢迎来到自助删除系统！自助删除，上不封顶，键入n退出。\n");

	for (;;) {//一次删除学生数据的过程
		printf("学生学号：");
		scanf("%s", &num);//读入学号
		getchar();//清除缓存区
		static int jump;//用于跳出外循环
		jump = 0;
		if (num == 'n')//n选项退出
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
		if (jump = 0) {//没找到
			printf("找不到该学生！请重新输入\n");
			continue;
		}
			
		//删除链表中的该项数据;
		if (local->next == local)
			strcpy(local->stu_num, "");
		else
			local->next = local->next->next;
	

		//用链表更新文件
		renew_data(local);//此时head已经不一定在删除后的链表中了
		printf("删除成功！\n\n");
	}
}

//获取链表——此函数用于获取当前文件内的数据并放入一个新定义的链表中，进行排序并返回该链表的头指针
Student* initialize_table() {
	static Student* old = NULL;//初始化一个old指针，用于记录当前链表指针，但它的初值为空
	free(old);//释放，确保内存空间不会浪费
	//获取链表长度
	int table_capacity = 0;//代表链表长度
	FILE* f = fopen("basic.csv", "r");//打开文件
	char temp_c;//临时变量，用于判断行数
	for (;;) {
		temp_c = fgetc(f);//读取文件内下一个字符
		if (temp_c == '\n') {
			table_capacity++;//；链表的长度+1
		}
		else if (temp_c == -1) {//文件结束
			fclose(f);
			break;
		}
	}
	//建立循环链表
	Student* head;//存放链表的头节点
	Student* local = (Student*)malloc(sizeof(Student));//local为链表的中间节点，此行生成的指针为链表的头节点
	head = local;
	for (int i = 0; i < table_capacity - 1; i++) {
		local->next = (Student*)malloc(sizeof(Student));//建立中间节点，并把他们都连起来，形成链表
		local = local->next;
	}
	local->next = head;//让链表的尾节点与头节点连接起来，形成循环链表

	get_data(head);//把目前文件里的数据读入链表中
	old = head;//记录下当前的链表头结点，下次启用该函数时释放该节点
	head = sort_link_table(head);//排序
	return head;//返回链表的头节点
}

//更新文件——根据已有链表对csv文件进行更新
void renew_data(Student* head) {
	head = sort_link_table(head);
	FILE* p_ini = fopen("basic.csv", "w");
	Student* local = head;
	for (;;) {
		if (local->stu_num != "") {
			fputs(strcat(local->stu_num, ","), p_ini);
			fputs(strcat(local->stu_name, ","), p_ini);
			fputs(strcat(local->stu_sex, ","), p_ini);
			fputs(strcat(local->stu_address, ","), p_ini);
			fputs(strcat(local->stu_phone_num, "\n"), p_ini);
			local = local->next;
		}
		if (local == head)
			break;
	}
	fclose(p_ini);
}


//排序——对文件内容按照学号从小到大排序）（不直接调用）
Student* sort_link_table(Student* head) {
	Student* p = head;//p为当前节点
	Student* p_later = p->next;//当前节点的下一个节点
	Student* p_front = p;//当前节点的上一个节点
	Student* temp;//temp中间变量，用于交换指针
	Student* tail = p;//存放尾节点
	int count = 0;//用于存放节点数
	do {
		count++;
		p = p->next;
	} while (p != head); //查看链表里有几个节点

	for (int i = 0; i < count - 1; i++) {//外层循环的次数为总节点数-1
		while(p->next != head){
			if (strcmp(p->stu_num, p_later->stu_num) > 0) {//若当前节点的学号大于下一个节点的学号时
				if (p == head) {//当前节点为头节点时

					while (tail->next != head) {//寻找尾节点
						tail = tail->next;
					}

					p->next = p_later->next;
					p_later->next = p;//此时p_later为头节点
					head = p_later;//更新头节点
					tail->next = head;//让尾节点指向新的头节点
				}
				else {//当前节点为中间节点时
					p->next = p_later->next;
					p_later->next = p;
					p_front->next = p_later;
				}
		/*此时p_later在head的前面，下面把p和p_later位置互换，保证p在p_later前面，方便后面判断*/
				temp = p_later;
				p_later = p;
				p = temp;
			}
			p_front = p;//让p_front始终在p的前面
			p = p->next;
			p_later = p_later->next;
		}
		/*外层循环结束，让p重新回到头节点，p_later回到p的下一个节点*/
		p = head;
		p_later = p->next;
	}
	return head;//返回头节点
}


//将csv文件中读到的学生数据写入初始化好的指针链表（不直接调用）
void get_data(Student* head) {
	FILE* p_ini = fopen("basic.csv", "r");//读方式打开文件
	Student* p = head;//记录下头指针
	int cell = 0;//所在的列
	char temp[5][30] = { NULL };//读取的格子内容
	for (;;) {//不断地遍历每一行
		static char point[2] = { "\0" };//当前指向的字符
		cell = 0;//将所在的列置为0
		for (;;) {//遍历一行的数据存入temp中
			point[0] = fgetc(p_ini);//读取一个字符
			if (point[0] == -1) {//文件结束
				break;//跳出
			}
			else if (point[0] == ',') {//遇到列分隔符
				cell++;//temp定位下标+1
			}
			else if (point[0] == '\n') {//遇到换行符

				break;//跳出，结算本行内容
			}
			else {//读取到正常文本内容
				strcat(temp[cell], point);//装到相应的罐子里
			}
		}


		//将temp的值赋到链表中
		strcpy(p->stu_num, temp[0]);
		strcpy(p->stu_name, temp[1]);
		strcpy(p->stu_sex, temp[2]);
		strcpy(p->stu_address, temp[3]);
		strcpy(p->stu_phone_num, temp[4]);



		//清空temp值
		for (int i = 0; i < 5; i++) {
			strcpy(temp[i], "");
		}

		//判断文件是否结束
		if (point[0] = fgetc(p_ini) == -1) {
			break;
		}
		else {
			fseek(p_ini, -1, SEEK_CUR);
			//链表向前
			p = p->next;
		}

	}
}


//对文件进行初始化
//void initialize_fire() {
//	FILE* p = fdopen("basic_测试.csv", "w");//p变量用于操控文件
//
//
//}


//浏览学生信息
void browse_data() {
	Student* head = initialize_table();
	Student* local = head;//保存头节点
	int col_width = 0;//列宽
	for (int i = 1;; i++) {//控制显示几行，具体行数由链表的节点数来控制
		for (int j = 1; j < 6; j++) {//显示5列

			//显示学号和姓名
			if (j < 3) {
				while (col_width < 14) {//前两列的列宽
					if (i == 1) {//第一行先输出属性名 学号 姓名
						printf(" ");
						col_width++;
						if (col_width == 5 && j == 1) {//居中显示
							col_width += printf("学号");
						}
						else if (col_width == 5 && j == 2) {//居中显示
							col_width += printf("姓名");
						}
					}
					else {
						if (j == 1) {//显示学号数据
							col_width += printf("%14s", local->stu_num);//输出最小宽度为14
						}
						else {//显示姓名数据
							col_width += printf("%14s", local->stu_name);//输出最小宽度为14
						}
					}
				}
				col_width = 0;//列宽清零
				printf("|");//作为列之间的分隔
			}

			//显示性别
			else if (j == 3) {
				while (col_width < 9) {
					if (i == 1) {//第一行先输出属性名 性别
						printf(" ");
						col_width++;
						if (col_width == 3) {//居中显示
							col_width += printf("性别");
						}
					}
					else {
						col_width += printf("%9s", local->stu_sex);//输出最小宽度为9
					}
					
					
				}
				col_width = 0;//列宽清0
				printf("|");//作为列之间的分隔
			}

			//显示联系电话
			else if (j == 4) {
				while (col_width < 12) {
					if (i == 1) {//第一行先输出属性名 联系电话
						printf(" ");
						col_width++;
						if (col_width == 2) {//居中显示
							col_width += printf("联系电话");
						}
					}
					else {
						col_width += printf("%12s", local->stu_phone_num);//输出最小宽度为12
					}
				}
				col_width = 0;
				printf("|");//作为列之间的分隔
			}

			//显示家庭地址
			else {
				while (col_width < 47) {
					if (i == 1) {//第一行先输出属性名 家庭地址
						printf(" ");
						col_width++;
						if (col_width == 20) {//居中显示
							col_width += printf("家庭地址");
						}
					}
					else {
						col_width += printf("%s", local->stu_address);//输出最小宽度为48
						break;
					}
				}
				col_width = 0;//作为列之间的分隔
			}
		}
		printf("\n");
		//输出一行 "-" ，用来作为行之间的分隔
		while (col_width < 100) {
			//每次到第一行列宽（|）的位置后，改为输出一个 "+"
			if (col_width == 14 || col_width == 29 || col_width == 39 || col_width == 52) {
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








#include "config.h"

//功能函数列表【5】
//创建——写学生信息的函数
void create_grade() {
	FILE* p_ini = fopen("grade.csv", "r");
	if (p_ini == 0) {
		p_ini = fopen("grade.csv", "w");
	}
	else {
		fclose(p_ini);
		p_ini = fopen("grade.csv", "a");
	}

	Student* head = initialize_table_grade();
	Student* new = head;
	for (;;) {
		printf("请输入学号为：%s的学生的各项成绩：\n", new->stu_num);
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
		printf("\n\n");
		if (new == head)
			break;
	}

	fclose(p_ini);
	renew_grade(head);
	printf("成绩录入成功!");
	system("pause");
}

//修改——修改学生信息模块
void alter_grade() {
	Student* head = initialize_table_grade();//获取链表
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

		//若修改了语数英的成绩，则重新计算主科平均成绩
		if (choice == 'd' || choice == 'e' || choice == 'f') {
			local->course.mark_comprehensive = (local->course.mark_avg_main_subject * 0.6) + (local->course.mark_peer * 0.1) \
				+ (local->course.mark_morality * 0.1) + (local->course.mark_avg_Tch * 0.2);
		}
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
		printf("\n\n\n");
	}

}

//删除——删除学生信息模块
void delete_grade() {
	Student* head = initialize_table_grade();//获取链表
	Student* local = head;//记录下头文件，用local进行操纵
	char num[15];//用户输入的学号
	printf("欢迎来到自助删除系统！自助删除，上不封顶，键入n退出。\n");
	printf("温馨提示：这里不删除学生的记录，只将学生的成绩信息清零，若要删除学生记录，请到学生库中操作！\n");

	for (;;) {//一次删除学生数据的过程
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

		//将链表中的该学生的成绩清零
		local->course.mark_Chinese = 0;
		local->course.mark_math = 0;
		local->course.mark_English = 0;
		local->course.mark_avg_main_subject = 0;
		local->course.rank_main_subject = 0;
		local->course.mark_peer = 0;
		local->course.mark_morality = 0;
		local->course.mark_avg_Tch = 0;
		local->course.mark_comprehensive = 0;
		local->course.rank_comprehensive = 0;


		//用链表更新文件
		renew_grade(local);//此时head已经不一定在删除后的链表中了
		printf("删除成功！\n\n");
	}
}

//查询——查询学生信息模块


//浏览学生信息



//读写函数【2】
//获取链表——此函数用于获取当前文件内的数据并放入一个新定义的链表中，进行排序并返回该链表的头指针
Student* initialize_table_grade() {
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

	get_grade(head);//把目前文件里的数据读入链表中
	old = head;//记录下当前的链表头结点，下次启用该函数时释放该节点
	head = sort_link_table_grade(head);//排序
	return head;//返回链表的头节点
}
//更新文件——根据已有链表对csv文件进行更新
void renew_grade(Student* head) {
	head = sort_link_table_grade(head);
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


//子函数列表【4】
//排序——对文件内容按照学号从小到大排序（不直接调用）
Student* sort_link_table_grade(Student* head) {
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
		while (p->next != head) {
			if (strcmp(p->stu_num, p_later->stu_num) > 0) {//若当前节点的学号大于下一个节点的学号时
				if (p == head) {//当前节点为头节点时

					if (count == 2) {//当节点数为2时，直接使头节点等于学号大的那个节点就行
						head = p_later;
					}
					else {
						while (tail->next != head) {//寻找尾节点
							tail = tail->next;
						}

						p->next = p_later->next;
						p_later->next = p;//此时p_later为头节点
						head = p_later;//更新头节点
						tail->next = head;//让尾节点指向新的头节点
					}
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
//写链表——将csv文件中读到的学生数据写入初始化好的指针链表（仅在initialize_table模块中调用）
void get_grade(Student* head) {
	FILE* p_ini = fopen("basic.csv", "r");//读方式打开文件
	FILE* p_init = fopen("grade.csv", "r");
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

		char temp_t[30] = {"\0"};
		fscanf(p_init, "%[^,],", temp_t);//把grade.csv文件里的第一个学号读出来，不存入链表中（起到一个占位的作用）
		fscanf(p_init, "%d,", &p->course.mark_Chinese);//获取语文成绩
		fscanf(p_init, "%d,", &p->course.mark_math);//获取数学成绩
		fscanf(p_init, "%d,", &p->course.mark_English);//获取英语成绩
		fscanf(p_init, "%f,", &p->course.mark_avg_main_subject);//获取主科平均分
		fscanf(p_init, "%d,", &p->course.rank_main_subject);//获取主科排名
		fscanf(p_init, "%d,", &p->course.mark_peer);//获取互拼分
		fscanf(p_init, "%d,", &p->course.mark_morality);//获取思想品德分数
		fscanf(p_init, "%d,", &p->course.mark_avg_Tch);//获取教师评价分数
		fscanf(p_init, "%f,", &p->course.mark_comprehensive);//获取综测分数
		fscanf(p_init, "%d\n", &p->course.rank_comprehensive);//获取综测排名

		

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

//使文件内容居中（browse_data的子函数，用于返回需要输出的空格数并输出空格）


//查询学生信息（browse_data的副函数，仅在select_basic模块中使用，对链表指针直接进行调用，用于输出表格）








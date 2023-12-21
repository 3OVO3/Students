#include "config.h"
#define stu_path "Student.txt"

//此函数用于获取当前文件内的数据并放入一个新定义的链表中，返回该链表的头指针
Student* initialize_table() {
	static Student* old=NULL;//初始化一个old指针，用于记录当前链表指针，但它的初值为空
	free(old);//释放，确保内存空间不会浪费
	//获取链表长度
	int table_capacity=0;//代表链表长度
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
	return head;//返回链表的头节点
}

//将csv文件中读到的学生数据写入初始化好的指针链表
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


//写学生信息的函数
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
}
 
//对文件内容按照学号从小到大排序
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
	head = p_later;
	return head;//返回头节点
}

//根据已有链表对csv文件进行更新
 void renew_data(Student*head) {
	 //sort_link_table(head);
	 FILE* p_ini = fopen("basic.csv", "w");
	 Student* local = head;
	 for (;;) {
		 fputs(strcat(local->stu_num, ","), p_ini);
		 fputs(strcat(local->stu_name, ","), p_ini);
		 fputs(strcat(local->stu_sex, ","), p_ini);
		 fputs(strcat(local->stu_address, ","), p_ini);
		 fputs(strcat(local->stu_phone_num, "\n"), p_ini);
		 local = local->next;
		 if (local == head)
			 break;
	 }
	 fclose(p_ini);
}

 //修改学生信息模块
void alter_basic() {
	Student* head = initialize_table();
	Student* local = head;
	FILE* p_ini = fopen("basic.csv", "r");
	char num[15];
	printf("请输入该学生的学号：");
	//如果不知道学号，可通过姓名查询学号
	scanf("%s", &num);
	for (;;) {//经过此循环，定位到学生位置
		if (!strcmp(local->stu_num, num))
			local = local->next;
		else
			break;
		if (local->next == head) {
			create_basic();
			return;
		}
	}
	char choice;//选项
	char temp[30];//输入的要修改值
	printf("请键入选项进行修改（a/学号 b/姓名 c/性别 d/住址 e/联系电话 n/退出修改）：");
	for (;;) {
		scanf("%c", &choice);
		if (choice == 'n')
			break;
		switch (choice)
		{
			printf("请输入修改后的值");
			scanf("%s", temp);
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
			printf("请重新输入选项哦");
			continue;
		}

		printf("修改成功！您是否还需要继续修改？（1继续，任意键退出）");
		scanf("%c", &choice);
		if (choice != '1')
			break;
		else
			printf("请键入选项进行修改（a/学号 b/姓名 c/性别 d/住址 e/联系电话 n/退出修改）：");
	}
	renew_data(head);//重新写入文件
	fclose(p_ini);//关闭文件
}


//对文件进行初始化
//void initialize_fire() {
//	FILE* p = fdopen("basic_测试.csv", "w");//p变量用于操控文件
//
//
//}




//浏览学生信息
// 睡前思路：
// 通过操控光标的位置，比如先在控制台的第二行画一行的 "-"
// 然后返回到上一行，输出文件第一行的内容(除了逗号以外的)，除了地址外其他属性（列）的宽度固定
// （需要把地址放在最后一列）
// 重复以上操作
//void browse() {
//	char s;//存放从文件中获取的字符
//	FILE* p = fopen("basic.csv", "r");
//	if (p == 0) {
//		printf("未写入学生信息！请先写入！");
//	}
//
//	for (int i = 0; s = fgetc(p) != -1; i++) {
//		if (s == ',') {
//			printf("%c", '|');
//		}
//		else if (s == '\n') {
//			printf("%c", '\n');
//			for (int i = 0; i < 101; i++) {
//				printf("%c", '-');
//			}
//			
//		}
//		else {
//			printf("%c", s);
//		}
//		
//	}
//}







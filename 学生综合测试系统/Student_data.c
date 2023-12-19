#include "config.h"
#define table_capacity 50
#define stu_path "Student.txt"

Student* initialize_table() {//建立链表
	static Student* head;//存放链表的头节点
	Student* local = (Student*)malloc(sizeof(Student));//local为链表的中间节点，此行生成的指针为链表的头节点
	head = local;
	for (int i = 0; i < table_capacity - 1; i++) {
		local->next = (Student*)malloc(sizeof(Student));//建立中间节点，并把他们都连起来，形成链表
		local = local->next;
	}
	local->next = head;//让链表的尾节点与头节点连接起来，形成循环链表
	return head;//返回链表的头节点
}



void input(Student* stu) {
	printf("请输入学生的学号：");
	scanf("%s", stu->stu_num);

	printf("请输入学生的姓名：");
	scanf("%s", stu->stu_name);

	printf("请输入学生的性别：");
	scanf("%s", stu->stu_sex);

	printf("请输入学生的家庭住址：");
	scanf("%s", stu->stu_address);


	printf("请输入学生的联系电话：");
	scanf("%s", stu->stu_phone_num);

}



void create_basic() {
	FILE* p_ini = fopen("basic.csv", "r");
	if (p_ini == 0) {
		p_ini = fopen("basic.csv", "w");
	}
	else {
		fclose(p_ini);
		fopen("basic.csv", "a");
	}
	Student *new=(Student*)malloc(sizeof(Student));
	input(new);
	setbuf(stdin, NULL);//使stdin输入流由默认缓冲区转为无缓冲区,达到清除缓存区的目的；
	fputs(strcat(new->stu_num, ","), p_ini);
	fputs(strcat(new->stu_name, ","), p_ini);
	fputs(strcat(new->stu_sex, ","), p_ini);
	fputs(strcat(new->stu_address, ","), p_ini);
	fputs(strcat(new->stu_phone_num, "\n"), p_ini);
	fclose(p_ini);
}







//
//void innitialize(){
//	Student* p = initialize_table;//p表示初始化完链表的头指针
//	FILE* f;//操纵文件的变量
//	f = fopen("Student.txt", "w");//读取文件，不存在则创建新的文件
//	for (int i = 0; i < table_capacity; i++) {
//		while (fgetc(f) != ",") {
//
//		}
//		
//	}
//}
//
////对文件进行初始化
//FILE* initialize_fire() {
//	FILE* p = fdopen(stu_path, "w");//p变量用于操控文件
//
//
//}

//
//

//
//
//
//
//
//
//
//
//
//
//







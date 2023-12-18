#include "config.h"
#define table_capacity 50
#define stu_path "Student.txt"



//对文件进行初始化
FILE* initialize_fire() {
	FILE* data_Student;//操纵文件的变量
	data_Student = fopen("Student.txt", "w");//读取文件，不存在则创建新的文件
	return data_Student;
}




void input(Student* stu) {
	initialize_fire();
	FILE* data = fopen(stu_path, "w");
	printf("请输入学生的学号：");
	scanf("%d",&stu->stu_num);
	fprintf(data,strcat("N\n",(char)stu->stu_num));

	printf("请输入学生的姓名：");
	scanf("%s", &stu->stu_num);
	fprintf(data, strcat("\n", stu->stu_name));

	printf("请输入学生的性别：");
	scanf("%d", &stu->stu_num);
	fprintf(data, strcat("\n", stu->stu_sex));
}









 initialize_table() {
	static Student* head;
	Student* local=(Student*)malloc(sizeof(Student));
	head = local;
	for (int i = 0; i < table_capacity-1; i++) {
		local->next= (Student*)malloc(sizeof(Student));
		local = local->next;
	}
	local->next = head;
	return head;
}

void add_new() {
	
}






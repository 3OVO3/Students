#include "config.h"
#define table_capacity 50
#define stu_path "Student.txt"



//���ļ����г�ʼ��
FILE* initialize_fire() {
	FILE* data_Student;//�����ļ��ı���
	data_Student = fopen("Student.txt", "w");//��ȡ�ļ����������򴴽��µ��ļ�
	return data_Student;
}




void input(Student* stu) {
	initialize_fire();
	FILE* data = fopen(stu_path, "w");
	printf("������ѧ����ѧ�ţ�");
	scanf("%d",&stu->stu_num);
	fprintf(data,strcat("N\n",(char)stu->stu_num));

	printf("������ѧ����������");
	scanf("%s", &stu->stu_num);
	fprintf(data, strcat("\n", stu->stu_name));

	printf("������ѧ�����Ա�");
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






#include "config.h"
#define table_capacity 50
#define stu_path "Student.txt"

Student* initialize_table() {//��������
	static Student* head;//��������ͷ�ڵ�
	Student* local = (Student*)malloc(sizeof(Student));//localΪ������м�ڵ㣬�������ɵ�ָ��Ϊ�����ͷ�ڵ�
	head = local;
	for (int i = 0; i < table_capacity - 1; i++) {
		local->next = (Student*)malloc(sizeof(Student));//�����м�ڵ㣬�������Ƕ����������γ�����
		local = local->next;
	}
	local->next = head;//�������β�ڵ���ͷ�ڵ������������γ�ѭ������
	return head;//���������ͷ�ڵ�
}



void input(Student* stu) {
	printf("������ѧ����ѧ�ţ�");
	scanf("%s", stu->stu_num);

	printf("������ѧ����������");
	scanf("%s", stu->stu_name);

	printf("������ѧ�����Ա�");
	scanf("%s", stu->stu_sex);

	printf("������ѧ���ļ�ͥסַ��");
	scanf("%s", stu->stu_address);


	printf("������ѧ������ϵ�绰��");
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
	setbuf(stdin, NULL);//ʹstdin��������Ĭ�ϻ�����תΪ�޻�����,�ﵽ�����������Ŀ�ģ�
	fputs(strcat(new->stu_num, ","), p_ini);
	fputs(strcat(new->stu_name, ","), p_ini);
	fputs(strcat(new->stu_sex, ","), p_ini);
	fputs(strcat(new->stu_address, ","), p_ini);
	fputs(strcat(new->stu_phone_num, "\n"), p_ini);
	fclose(p_ini);
}







//
//void innitialize(){
//	Student* p = initialize_table;//p��ʾ��ʼ���������ͷָ��
//	FILE* f;//�����ļ��ı���
//	f = fopen("Student.txt", "w");//��ȡ�ļ����������򴴽��µ��ļ�
//	for (int i = 0; i < table_capacity; i++) {
//		while (fgetc(f) != ",") {
//
//		}
//		
//	}
//}
//
////���ļ����г�ʼ��
//FILE* initialize_fire() {
//	FILE* p = fdopen(stu_path, "w");//p�������ڲٿ��ļ�
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







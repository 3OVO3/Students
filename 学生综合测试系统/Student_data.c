#include "config.h"
#define table_capacity 50
#define stu_path "Student.txt"
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



int create_basic() {
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
	printf("%s",new->stu_name);
	fputs(strcat(new->stu_num,","),p_ini);
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
// student *initialize_table() {
//	static student* head;
//	student* local=(student*)malloc(sizeof(student));
//	head = local;
//	for (int i = 0; i < table_capacity-1; i++) {
//		local->next= (student*)malloc(sizeof(student));
//		local = local->next;
//	}
//	local->next = head;
//	return head;
//}
//
//
//



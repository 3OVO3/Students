#include "config.h"
#define table_capacity 50
#define stu_path "Student.txt"

Student* initialize_table() {
	static Student* head;
	Student* local = (Student*)malloc(sizeof(Student));
	head = local;
	for (int i = 0; i < table_capacity - 1; i++) {
		local->next = (Student*)malloc(sizeof(Student));
		local = local->next;
	}
	local->next = head;
	return head;
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

void get_data(Student*head) {
	FILE* p_ini = fopen("basic.csv", "r");//����ʽ���ļ�
	Student* p = head;//��¼��ͷָ��
	
	int cell=0;//���ڵ���
	char temp[5][30] = {NULL};//��ȡ�ĸ�������
	for (;;) {//���ϵر���ÿһ��
		static char point[2] = { "\0" };//��ǰָ����ַ�
		cell = 0;//�����ڵ�����Ϊ0
		for (;;) {//����һ�е����ݴ���temp��
			point[0] = fgetc(p_ini);//��ȡһ���ַ�
			if (point[0] == -1) {//�ļ�����
				break;//����
			}
			else if (point[0] == ',') {//�����зָ���
				cell++;//temp��λ�±�+1
			}
			else if (point[0] == '\n') {//�������з�
				break;//���������㱾������
			}
			else {//��ȡ�������ı�����
				strcat(temp[cell], point);//װ����Ӧ�Ĺ�����
			}
		}

		
		//��temp��ֵ����������
		strcpy(head->stu_num, temp[0]);
		strcpy(head->stu_name, temp[1]);
		strcpy(head->stu_sex, temp[2]);
		strcpy(head->stu_address, temp[3]);
		strcpy(head->stu_phone_num, temp[4]);
		
		

		//���tempֵ
		for (int i = 0; i < 5; i++) {
			strcpy(temp[i], "");
		}

		//�ж��ļ��Ƿ����
		if (point[0] = fgetc(p_ini) == -1) {
			break;
		}
		else {
			//������ǰ
			head = head->next;
		}
			
	}
	head->next=p;//��head����Ϊ����ͷ���
}

//дѧ����Ϣ�ĺ���
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
	input(new);
	
	fputs(strcat(new->stu_num,","),p_ini);
	fputs(strcat(new->stu_name, ","), p_ini);
	fputs(strcat(new->stu_sex, ","), p_ini);
	fputs(strcat(new->stu_address, ","), p_ini);
	fputs(strcat(new->stu_phone_num, "\n"), p_ini);
	fclose(p_ini);
}
 
void csv_to_link() {
	FILE* f = fopen("basic.csv", "r");
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

//
//
//



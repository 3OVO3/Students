#include "config.h"
#define stu_path "Student.txt"

//�˺������ڻ�ȡ��ǰ�ļ��ڵ����ݲ�����һ���¶���������У����ظ������ͷָ��
Student* initialize_table() {
	static Student* old=NULL;//��ʼ��һ��oldָ�룬���ڼ�¼��ǰ����ָ�룬�����ĳ�ֵΪ��
	free(old);//�ͷţ�ȷ���ڴ�ռ䲻���˷�
	//��ȡ������
	int table_capacity=0;//����������
	FILE* f = fopen("basic.csv", "r");//���ļ�
	char temp_c;//��ʱ�����������ж�����
	for (;;) {
		temp_c = fgetc(f);//��ȡ�ļ�����һ���ַ�
		if (temp_c == '\n') {
			table_capacity++;//������ĳ���+1
		}
		else if (temp_c == -1) {//�ļ�����
			fclose(f);
			break;
		}		
	}
	//����ѭ������
	Student* head;//��������ͷ�ڵ�
	Student* local = (Student*)malloc(sizeof(Student));//localΪ������м�ڵ㣬�������ɵ�ָ��Ϊ�����ͷ�ڵ�
	head = local;
	for (int i = 0; i < table_capacity - 1; i++) {
		local->next = (Student*)malloc(sizeof(Student));//�����м�ڵ㣬�������Ƕ����������γ�����
		local = local->next;
	}
	local->next = head;//�������β�ڵ���ͷ�ڵ������������γ�ѭ������

	get_data(head);//��Ŀǰ�ļ�������ݶ���������
	old = head;//��¼�µ�ǰ������ͷ��㣬�´����øú���ʱ�ͷŸýڵ�
	return head;//���������ͷ�ڵ�
}

//��csv�ļ��ж�����ѧ������д���ʼ���õ�ָ������
void get_data(Student* head) {
	FILE* p_ini = fopen("basic.csv", "r");//����ʽ���ļ�
	Student* p = head;//��¼��ͷָ��
	int cell = 0;//���ڵ���
	char temp[5][30] = { NULL };//��ȡ�ĸ�������
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
		strcpy(p->stu_num, temp[0]);
		strcpy(p->stu_name, temp[1]);
		strcpy(p->stu_sex, temp[2]);
		strcpy(p->stu_address, temp[3]);
		strcpy(p->stu_phone_num, temp[4]);



		//���tempֵ
		for (int i = 0; i < 5; i++) {
			strcpy(temp[i], "");
		}

		//�ж��ļ��Ƿ����
		if (point[0] = fgetc(p_ini) == -1) {
			break;
		}
		else {
			fseek(p_ini, -1, SEEK_CUR);
			//������ǰ
			p = p->next;
		}

	}
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

	printf("������ѧ����ѧ�ţ�");
	scanf("%s",new->stu_num);

	printf("������ѧ����������");
	scanf("%s",new->stu_name);

	printf("������ѧ�����Ա�");
	scanf("%s",new->stu_sex);

	printf("������ѧ���ļ�ͥסַ��");
	scanf("%s",new->stu_address);


	printf("������ѧ������ϵ�绰��");
	scanf("%s",new->stu_phone_num);

	setbuf(stdin, NULL);//ʹstdin��������Ĭ�ϻ�����תΪ�޻�����,�ﵽ�����������Ŀ��
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
 
//���ļ����ݰ���ѧ�Ŵ�С��������
Student* sort_link_table(Student* head) {
	Student* p = head;//pΪ��ǰ�ڵ�
	Student* p_later = p->next;//��ǰ�ڵ����һ���ڵ�
	Student* p_front = p;//��ǰ�ڵ����һ���ڵ�
	Student* temp;//temp�м���������ڽ���ָ��
	Student* tail = p;//���β�ڵ�
	int count = 0;//���ڴ�Žڵ���
	do {
		count++;
		p = p->next;
	} while (p != head); //�鿴�������м����ڵ�

	for (int i = 0; i < count - 1; i++) {//���ѭ���Ĵ���Ϊ�ܽڵ���-1
		while(p->next != head){
			if (strcmp(p->stu_num, p_later->stu_num) > 0) {//����ǰ�ڵ��ѧ�Ŵ�����һ���ڵ��ѧ��ʱ
				if (p == head) {//��ǰ�ڵ�Ϊͷ�ڵ�ʱ

					while (tail->next != head) {//Ѱ��β�ڵ�
						tail = tail->next;
					}

					p->next = p_later->next;
					p_later->next = p;//��ʱp_laterΪͷ�ڵ�
					head = p_later;//����ͷ�ڵ�
					tail->next = head;//��β�ڵ�ָ���µ�ͷ�ڵ�
				}
				else {//��ǰ�ڵ�Ϊ�м�ڵ�ʱ
					p->next = p_later->next;
					p_later->next = p;
					p_front->next = p_later;
				}
		/*��ʱp_later��head��ǰ�棬�����p��p_laterλ�û�������֤p��p_laterǰ�棬��������ж�*/
				temp = p_later;
				p_later = p;
				p = temp;
			}
			p_front = p;//��p_frontʼ����p��ǰ��
			p = p->next;
			p_later = p_later->next;
		}
		/*���ѭ����������p���»ص�ͷ�ڵ㣬p_later�ص�p����һ���ڵ�*/
		p = head;
		p_later = p->next;
	}
	head = p_later;
	return head;//����ͷ�ڵ�
}

//�������������csv�ļ����и���
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

 //�޸�ѧ����Ϣģ��
void alter_basic() {
	Student* head = initialize_table();
	Student* local = head;
	FILE* p_ini = fopen("basic.csv", "r");
	char num[15];
	printf("�������ѧ����ѧ�ţ�");
	//�����֪��ѧ�ţ���ͨ��������ѯѧ��
	scanf("%s", &num);
	for (;;) {//������ѭ������λ��ѧ��λ��
		if (!strcmp(local->stu_num, num))
			local = local->next;
		else
			break;
		if (local->next == head) {
			create_basic();
			return;
		}
	}
	char choice;//ѡ��
	char temp[30];//�����Ҫ�޸�ֵ
	printf("�����ѡ������޸ģ�a/ѧ�� b/���� c/�Ա� d/סַ e/��ϵ�绰 n/�˳��޸ģ���");
	for (;;) {
		scanf("%c", &choice);
		if (choice == 'n')
			break;
		switch (choice)
		{
			printf("�������޸ĺ��ֵ");
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
			printf("����������ѡ��Ŷ");
			continue;
		}

		printf("�޸ĳɹ������Ƿ���Ҫ�����޸ģ���1������������˳���");
		scanf("%c", &choice);
		if (choice != '1')
			break;
		else
			printf("�����ѡ������޸ģ�a/ѧ�� b/���� c/�Ա� d/סַ e/��ϵ�绰 n/�˳��޸ģ���");
	}
	renew_data(head);//����д���ļ�
	fclose(p_ini);//�ر��ļ�
}


//���ļ����г�ʼ��
//void initialize_fire() {
//	FILE* p = fdopen("basic_����.csv", "w");//p�������ڲٿ��ļ�
//
//
//}




//���ѧ����Ϣ
// ˯ǰ˼·��
// ͨ���ٿع���λ�ã��������ڿ���̨�ĵڶ��л�һ�е� "-"
// Ȼ�󷵻ص���һ�У�����ļ���һ�е�����(���˶��������)�����˵�ַ���������ԣ��У��Ŀ�ȹ̶�
// ����Ҫ�ѵ�ַ�������һ�У�
// �ظ����ϲ���
//void browse() {
//	char s;//��Ŵ��ļ��л�ȡ���ַ�
//	FILE* p = fopen("basic.csv", "r");
//	if (p == 0) {
//		printf("δд��ѧ����Ϣ������д�룡");
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







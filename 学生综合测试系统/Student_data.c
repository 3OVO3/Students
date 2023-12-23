#include "config.h"
#define stu_path "Student.txt"


//��������дѧ����Ϣ�ĺ���
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
	printf("�����ɹ���");
}

//�޸ġ����޸�ѧ����Ϣģ��
void alter_basic() {
	Student* head = initialize_table();//��ȡ����
	Student* local = head;//��¼��ͷ�ļ�����local���в���
	FILE* p_ini = fopen("basic.csv", "r");//���ļ�
	char num[15];//�û������ѧ��
	printf("�������ѧ����ѧ�ţ�");
	//�����֪��ѧ�ţ���ͨ��������ѯѧ��
	scanf("%s", &num);//����ѧ��
	getchar();//���������
	for (;;) {//������ѭ������λ��ѧ��λ��
		//printf("%s\n", local->stu_num);
		if (strcmp(local->stu_num, num))//������Ϊ0�����������������ű�����һ��
			local = local->next;//������
		else
			break;
		if (local == head) {//�Ҳ���
			printf("�Ҳ�����ѧ�����������´�����ѧ����\n");
			create_basic();//����ѧ������
			getchar();
			return;//�˳�
		}
	}
	char choice;//ѡ��
	char temp[30];//�����Ҫ�޸�ֵ
	printf("�����ѡ������޸ģ�a/ѧ�� b/���� c/�Ա� d/סַ e/��ϵ�绰 n/�˳��޸ģ���");
	for (;;) {
		scanf("%c", &choice);
		if (choice == 'n')
			break;
		printf("�������޸ĺ��ֵ");
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
			printf("����������ѡ��Ŷ");
			continue;
		}
		renew_data(head);//����д���ļ�
		printf("�޸ĳɹ������Ƿ���Ҫ�����޸ģ���1������������˳���");
		scanf("%c", &choice);
		getchar();
		if (choice != '1')
			break;
		else
			printf("�����ѡ������޸ģ�a/ѧ�� b/���� c/�Ա� d/סַ e/��ϵ�绰 n/�˳��޸ģ���");
	}
	
	fclose(p_ini);//�ر��ļ�
}
 
//ɾ������ɾ��ѧ����Ϣģ��
void delete_basic() {
	Student* head = initialize_table();//��ȡ����

	Student* local = head;//��¼��ͷ�ļ�����local���в���
	FILE* p_ini = fopen("basic.csv", "r");//���ļ�
	char num[15];//�û������ѧ��
	printf("�������ѧ����ѧ�ţ�");
	for (;;) {//������ѭ������λ��ѧ��λ��
		if (num == 'n')//nѡ���˳�
			break;
		scanf("%s", &num);//����ѧ��
		getchar();//���������
		if (strcmp(local->stu_num, num))//������Ϊ0�����������������ű�����һ��
			local = local->next;//������
		else
			break;
		if (local == head) {//�Ҳ���
			printf("�Ҳ�����ѧ��������������ѧ�ţ���n�˳���\n");
			continue;
		}
	}

	fclose(p_ini);//�ر��ļ�����ʼ���գ�
}

//��ȡ�������˺������ڻ�ȡ��ǰ�ļ��ڵ����ݲ�����һ���¶���������У��������򲢷��ظ������ͷָ��
Student* initialize_table() {
	static Student* old = NULL;//��ʼ��һ��oldָ�룬���ڼ�¼��ǰ����ָ�룬�����ĳ�ֵΪ��
	free(old);//�ͷţ�ȷ���ڴ�ռ䲻���˷�
	//��ȡ������
	int table_capacity = 0;//����������
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
	head = sort_link_table(head);
	return head;//���������ͷ�ڵ�
}

//�����ļ������������������csv�ļ����и���
void renew_data(Student* head) {
	head = sort_link_table(head);
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


//���򡪡����ļ����ݰ���ѧ�Ŵ�С�������򣩣���ֱ�ӵ��ã�
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
	return head;//����ͷ�ڵ�
}


//��csv�ļ��ж�����ѧ������д���ʼ���õ�ָ��������ֱ�ӵ��ã�
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


//���ļ����г�ʼ��
//void initialize_fire() {
//	FILE* p = fdopen("basic_����.csv", "w");//p�������ڲٿ��ļ�
//
//
//}


//���ѧ����Ϣ
void browse_data() {
	Student* head = initialize_table();
	Student* local = head;//����ͷ�ڵ�
	int col_width = 0;//�п�
	for (int i = 1;; i++) {//������ʾ���У���������������Ľڵ���������
		for (int j = 1; j < 6; j++) {//��ʾ5��

			//��ʾѧ�ź�����
			if (j < 3) {
				while (col_width < 14) {//ǰ���е��п�
					if (i == 1) {//��һ������������� ѧ�� ����
						printf(" ");
						col_width++;
						if (col_width == 5 && j == 1) {//������ʾ
							col_width += printf("ѧ��");
						}
						else if (col_width == 5 && j == 2) {//������ʾ
							col_width += printf("����");
						}
					}
					else {
						if (j == 1) {//��ʾѧ������
							col_width += printf("%14s", local->stu_num);//�����С���Ϊ14
						}
						else {//��ʾ��������
							col_width += printf("%14s", local->stu_name);//�����С���Ϊ14
						}
					}
				}
				col_width = 0;//�п�����
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ�Ա�
			else if (j == 3) {
				while (col_width < 9) {
					if (i == 1) {//��һ������������� �Ա�
						printf(" ");
						col_width++;
						if (col_width == 3) {//������ʾ
							col_width += printf("�Ա�");
						}
					}
					else {
						col_width += printf("%9s", local->stu_sex);//�����С���Ϊ9
					}
					
					
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ��ϵ�绰
			else if (j == 4) {
				while (col_width < 12) {
					if (i == 1) {//��һ������������� ��ϵ�绰
						printf(" ");
						col_width++;
						if (col_width == 2) {//������ʾ
							col_width += printf("��ϵ�绰");
						}
					}
					else {
						col_width += printf("%12s", local->stu_phone_num);//�����С���Ϊ12
					}
				}
				col_width = 0;
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ��ͥ��ַ
			else {
				while (col_width < 47) {
					if (i == 1) {//��һ������������� ��ͥ��ַ
						printf(" ");
						col_width++;
						if (col_width == 20) {//������ʾ
							col_width += printf("��ͥ��ַ");
						}
					}
					else {
						col_width += printf("%s", local->stu_address);//�����С���Ϊ48
						break;
					}
				}
				col_width = 0;//��Ϊ��֮��ķָ�
			}
		}
		printf("\n");
		//���һ�� "-" ��������Ϊ��֮��ķָ�
		while (col_width < 100) {
			//ÿ�ε���һ���п�|����λ�ú󣬸�Ϊ���һ�� "+"
			if (col_width == 14 || col_width == 29 || col_width == 39 || col_width == 52) {
				printf("+");
			}
			else {
				printf("-");
			}
			col_width++;
		}
		col_width = 0;//�п�����
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








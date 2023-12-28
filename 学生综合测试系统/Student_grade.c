#include "config.h"

//���ܺ����б�5��
//��������дѧ����Ϣ�ĺ���
void create_grade() {

	FILE* p_ini = fopen("grade.csv", "r");
	if (p_ini == 0) {
		p_ini = fopen("grade.csv", "w");
	}
	else {
		fclose(p_ini);
		p_ini = fopen("grade.csv", "a");
	}

	Course* new = (Course*)malloc(sizeof(Course));


	printf("������ѧ����ѧ�ţ�");
	scanf("%s", new->stu_num);

	printf("������ѧ����������");
	scanf("%s", new->stu_name);

	printf("������ѧ�����Ա�");
	scanf("%s", new->stu_sex);

	printf("������ѧ���ļ�ͥסַ��");
	scanf("%s", new->stu_address);


	printf("������ѧ������ϵ�绰��");
	scanf("%s", new->stu_phone_num);

	setbuf(stdin, NULL);//ʹstdin��������Ĭ�ϻ�����תΪ�޻�����,�ﵽ�����������Ŀ��
	fputs(strcat(new->stu_num, ","), p_ini);
	fputs(strcat(new->stu_name, ","), p_ini);
	fputs(strcat(new->stu_sex, ","), p_ini);
	fputs(strcat(new->stu_address, ","), p_ini);
	fputs(strcat(new->stu_phone_num, "\n"), p_ini);
	fclose(p_ini);
	Student* head;
	head = initialize_table_grade();
	renew_grade(head);
	printf("�����ɹ�������1�������(������˳�)��\n");
	if (_getch() == '1') {
		printf("\n\n");
		create_grade();
	}
}

//�޸ġ����޸�ѧ����Ϣģ��
void alter_grade() {
	Student* head = initialize_table_grade();//��ȡ����
	Student* local = head;//��¼��ͷ�ļ�����local���в���
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
			create_grade();//����ѧ������
			return;//�˳�
		}
	}
	char choice;//ѡ��
	char temp[30];//�����Ҫ�޸�ֵ

	for (;;) {
		printf("�����ѡ������޸ģ�a/ѧ�� b/���� c/�Ա� d/סַ e/��ϵ�绰 n/�˳��޸ģ���");
		scanf("%c", &choice);
		while (getchar() != '\n');//������л�����
		char choices[7] = "abcden";
		int bool = 0;
		for (int i = 0; i < 6; i++) {
			if (choice == choices[i])
				bool = 1;
		}
		if (bool == 0) {
			printf("�������ѡ���������������룡\n");
			continue;
		}

		if (choice == 'n')//nѡ���˳�
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
			break;
		}


		renew_grade(head);//����д���ļ�

		printf("�޸ĳɹ������Ƿ���Ҫ�����޸ģ���1������������˳���");
		scanf("%c", &choice);
		getchar();
		if (choice != '1')
			break;
	}

}

//ɾ������ɾ��ѧ����Ϣģ��
void delete_grade() {
	Student* head = initialize_table_grade();//��ȡ����
	Student* local = head;//��¼��ͷ�ļ�����local���в���
	char num[15];//�û������ѧ��
	printf("��ӭ��������ɾ��ϵͳ������ɾ�����ϲ��ⶥ������n�˳���\n");

	for (;;) {//һ��ɾ��ѧ�����ݵĹ���
		printf("ѧ��ѧ�ţ�");
		scanf("%s", &num);//����ѧ��
		getchar();//���������
		static int jump;//����������ѭ��
		jump = 0;
		if (!strcmp(num, "n"))//nѡ���˳�  
			break;
		for (;;) {//��ѭ�������ҵ�ѧ��λ�õ�ǰһ��
			if (strcmp(local->next->stu_num, num))//������Ϊ0�����������������ű�����һ��
				local = local->next;//������
			else {
				jump = 1;
				break;
			}

			if (local == head) {//�Ҳ��� 
				break;
			}
		}
		if (jump == 0) {//û�ҵ�
			printf("�Ҳ�����ѧ��������������\n");
			continue;
		}

		//ɾ�������еĸ�������;
		if (local->next == local)
			strcpy(local->stu_num, "");
		else
			local->next = local->next->next;


		//����������ļ�
		renew_grade(local);//��ʱhead�Ѿ���һ����ɾ�������������
		printf("ɾ���ɹ���\n\n");
	}
}

//��ѯ������ѯѧ����Ϣģ��
void select_grade() {
	//����Ѱ��ѧ�����ڽڵ����޸ĺ���ͬ��
	Student* head = initialize_table_grade();//��ȡ����
	Student* local = head;//��¼��ͷ�ļ�����local���в���
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
			system("pause");
			system("cls");//����
			create_grade();//����ѧ������
			system("cls");//����
			select_grade();
			return;//�˳�
		}
	}

	Student* new_one = (Student*)malloc(sizeof(Student));
	new_one->next = new_one;
	strcpy(new_one->stu_num, local->stu_num);
	strcpy(new_one->stu_name, local->stu_name);
	strcpy(new_one->stu_sex, local->stu_sex);
	strcpy(new_one->stu_phone_num, local->stu_phone_num);
	strcpy(new_one->stu_address, local->stu_address);


	table_head_input_grade(new_one);


	printf("\n\n");
	printf("1������ѯ��������˳���\n");
	static char c;
	c = _getch();
	if (c != '1')
		return;
	else
		select_grade();


}

//���ѧ����Ϣ
void browse_grade() {
	Student* head = initialize_table_grade();
	Student* local = head;//����ͷ�ڵ�
	int col_width = 0;//�п�
	for (int i = 1;; i++) {//������ʾ���У���������������Ľڵ���������
		for (int j = 1; j < 13; j++) {//��ʾ5��

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
							col_width += browe_center_grade(14, strlen(local->stu_num));
							col_width += printf("%s", local->stu_num);
							col_width += browe_center_grade(14, strlen(local->stu_num));
						}
						else {//��ʾ��������
							col_width += browe_center_grade(14, strlen(local->stu_name));
							col_width += printf("%s", local->stu_name);
							col_width += browe_center(14, strlen(local->stu_name));
						}
					}
				}
				col_width = 0;//�п�����
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ���ķ���
			else if (j == 3) {
				while (col_width < 4) {
					if (i == 1) {//��һ������������� ����
						col_width += printf("����");
					}
					else {
			            /*�������󳤶ȵķ�λ����������10Ϊ�׵Ķ�����Ȼ��ȡ���������ټ�1*/
						col_width += browe_center(6, ((int)log10(local->course_data->mark_Chinese)) + 1);
						col_width += printf("%d", local->course_data->mark_Chinese);
						col_width += browe_center(6, ((int)log10(local->course_data->mark_Chinese)) + 1);
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ��ѧ�ɼ�
			else if (j == 4) {
				while (col_width < 4) {
					if (i == 1) {//��һ������������� ��ѧ
						col_width += printf("��ѧ");
					}
					else {
						col_width += browe_center(6, ((int)log10(local->course_data->mark_math)) + 1);
						col_width += printf("%d", local->course_data->mark_math);
						col_width += browe_center(6, ((int)log10(local->course_data->mark_math)) + 1);
					}
				}
				col_width = 0;
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾӢ��ɼ�
			else if(j == 5){
				while (col_width < 4) {
					if (i == 1) {//��һ������������� Ӣ��
						col_width += printf("Ӣ��");
					}
					else {
						col_width += browe_center(6, ((int)log10(local->course_data->mark_English)) + 1);
						col_width += printf("%s", local->course_data->mark_English);
						col_width += browe_center(6, ((int)log10(local->course_data->mark_English)) + 1);
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}
			//��ʾ����ƽ����
			else if (j == 6) {
				while (col_width < 10) {
					if (i == 1) {//��һ������������� ����ƽ����
						col_width += printf("����ƽ����");
					}
					else {
						col_width += browe_center(6, ((int)log10(local->course_data->mark_avg_main_subject)) + 1);
						col_width += printf("%s", local->course_data->mark_avg_main_subject);
						col_width += browe_center(6, ((int)log10(local->course_data->mark_avg_main_subject)) + 1);
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}
			//��ʾ��������
			else if (j == 7) {
				while (col_width < 10) {
					if (i == 1) {//��һ������������� ��������
						col_width += printf("��������");
					}
					else {
						col_width += browe_center(6, ((int)log10(local->course_data->rank_main_subject)) + 1);
						col_width += printf("%s", local->course_data->rank_main_subject);
						col_width += browe_center(6, ((int)log10(local->course_data->rank_main_subject)) + 1);
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}
			//��ʾ������
			else if (j == 7) {
				while (col_width < 10) {
					if (i == 1) {//��һ������������� ��������
						col_width += printf("��������");
					}
					else {
						col_width += browe_center(6, ((int)log10(local->course_data->rank_main_subject)) + 1);
						col_width += printf("%s", local->course_data->rank_main_subject);
						col_width += browe_center(6, ((int)log10(local->course_data->rank_main_subject)) + 1);
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
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


//��д������2��
//��ȡ�������˺������ڻ�ȡ��ǰ�ļ��ڵ����ݲ�����һ���¶���������У��������򲢷��ظ������ͷָ��
Course* initialize_table_grade() {
	static Course* old = NULL;//��ʼ��һ��oldָ�룬���ڼ�¼��ǰ����ָ�룬�����ĳ�ֵΪ��
	free(old);//�ͷţ�ȷ���ڴ�ռ䲻���˷�
	//��ȡ������
	int table_capacity = 0;//����������
	FILE* f = fopen("grade.csv", "r");//���ļ�
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
	Course* head;//��������ͷ�ڵ�
	Course* local = (Course*)malloc(sizeof(Course));//localΪ������м�ڵ㣬�������ɵ�ָ��Ϊ�����ͷ�ڵ�
	head = local;
	for (int i = 0; i < table_capacity - 1; i++) {
		local->next = (Student*)malloc(sizeof(Student));//�����м�ڵ㣬�������Ƕ����������γ�����
		local = local->next;
	}
	local->next = head;//�������β�ڵ���ͷ�ڵ������������γ�ѭ������

	get_grade(head);//��Ŀǰ�ļ�������ݶ���������
	old = head;//��¼�µ�ǰ������ͷ��㣬�´����øú���ʱ�ͷŸýڵ�
	head = sort_link_table_grade(head);//����
	return head;//���������ͷ�ڵ�
}

//�����ļ������������������csv�ļ����и���
void renew_grade(Student* head) {
	head = sort_link_table_grade(head);
	FILE* p_ini = fopen("basic.csv", "w");
	Student* local = head;
	char temp[30] = { NULL };
	for (;;) {
		if (strcmp(local->stu_num, "")) {
			strcpy(temp, local->stu_num);
			fputs(strcat(temp, ","), p_ini);

			strcpy(temp, local->stu_name);
			fputs(strcat(temp, ","), p_ini);

			strcpy(temp, local->stu_sex);
			fputs(strcat(temp, ","), p_ini);

			strcpy(temp, local->stu_address);
			fputs(strcat(temp, ","), p_ini);

			strcpy(temp, local->stu_phone_num);
			fputs(strcat(temp, "\n"), p_ini);

			local = local->next;
		}
		if (local == head)
			break;
	}
	fclose(p_ini);
}


//�Ӻ����б�4��
//���򡪡����ļ����ݰ���ѧ�Ŵ�С�������򣨲�ֱ�ӵ��ã�
Course* sort_link_table_grade(Student* head) {
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
		while (p->next != head) {
			if (strcmp(p->stu_num, p_later->stu_num) > 0) {//����ǰ�ڵ��ѧ�Ŵ�����һ���ڵ��ѧ��ʱ
				if (p == head) {//��ǰ�ڵ�Ϊͷ�ڵ�ʱ

					if (count == 2) {//���ڵ���Ϊ2ʱ��ֱ��ʹͷ�ڵ����ѧ�Ŵ���Ǹ��ڵ����
						head = p_later;
					}
					else {
						while (tail->next != head) {//Ѱ��β�ڵ�
							tail = tail->next;
						}

						p->next = p_later->next;
						p_later->next = p;//��ʱp_laterΪͷ�ڵ�
						head = p_later;//����ͷ�ڵ�
						tail->next = head;//��β�ڵ�ָ���µ�ͷ�ڵ�
					}
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

//д��������csv�ļ��ж�����ѧ������д���ʼ���õ�ָ����������initialize_tableģ���е��ã�
void get_grade(Course* head) {
	FILE* p_ini = fopen("grade.csv", "r");//����ʽ���ļ�
	Course* p = head;//��¼��ͷָ��
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

//ʹ�ļ����ݾ��У�browse_data���Ӻ��������ڷ�����Ҫ����Ŀո���������ո�
int browe_center_grade(int col_width, int len) {
	static int flag = 0;//��־λ Ϊ1ʱ�������ߵĿո� Ϊ2ʱ������ұߵĿո�
	int left_space = (col_width - len) / 2;//��ߵĿո���
	int right_space = (col_width - len) - left_space;//�ұߵĿո���
	int count = 0;//���ڷ��������˵Ŀո�����
	if ((left_space != right_space) && flag == 0) {//���������߿ո��������ʱ
		flag = 1;
	}
	else if (left_space == right_space) {//���������߿ո������ʱ
		for (int i = 0; i < left_space; i++) {
			count += printf(" ");
		}
	}
	if (flag == 1) {//�������߿ո�������ȣ���һ�ν����ú���ʱ�����ߵĿո�
		for (int i = 0; i < left_space; i++) {
			count += printf(" ");
		}
		flag = 2;
	}
	else if (flag == 2) {//�������߿ո�������ȣ��ڶ��ν����ú���ʱ����ұߵĿո�
		for (int i = 0; i < right_space; i++) {
			count += printf(" ");
		}
		flag = 0;
	}

	return count;
}

//��ѯѧ����Ϣ��browse_data�ĸ�����������select_basicģ����ʹ�ã�������ָ��ֱ�ӽ��е��ã�����������
void table_head_input_grade(Student* head) {
	Student* local = head;
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
							col_width += browe_center(14, strlen(local->stu_num));
							col_width += printf("%s", local->stu_num);
							col_width += browe_center(14, strlen(local->stu_num));
						}
						else {//��ʾ��������
							col_width += browe_center(14, strlen(local->stu_name));
							col_width += printf("%s", local->stu_name);
							col_width += browe_center(14, strlen(local->stu_name));
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
						col_width += browe_center(9, strlen(local->stu_sex));
						col_width += printf("%s", local->stu_sex);
						col_width += browe_center(9, strlen(local->stu_sex));
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
						col_width += browe_center(12, strlen(local->stu_phone_num));
						col_width += printf("%s", local->stu_phone_num);
						col_width += browe_center(12, strlen(local->stu_phone_num));
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
						col_width += browe_center(47, strlen(local->stu_address));
						col_width += printf("%s", local->stu_address);
						col_width += browe_center(47, strlen(local->stu_address));
						break;
					}
				}
				col_width = 0;
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
}








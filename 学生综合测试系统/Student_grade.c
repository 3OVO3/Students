#include "config.h"

//���ܺ����б�5��
//��������дѧ����Ϣ�ĺ���
void create_grade() {
	Student* head = initialize_table();
	Student* new = head;
	for (;;) {
		//����ǰ��ѧ��������ƽ�����������۲�����Ϊ0����ʾ��ǰѧ���������ģ���Ҫ¼��ɼ�
		if (new->course.rank_main_subject == 0 || new->course.rank_comprehensive == 0) {
			printf("������ѧ��Ϊ%s��ѧ���ĸ���ɼ���\n", new->stu_num);
			for (int i = 1; i < 7; i++) {
				switch (i) {
				case 1:
					printf("���������ĳɼ���");
					scanf("%d", &new->course.mark_Chinese);
					break;
				case 2:
					printf("��������ѧ�ɼ���");
					scanf("%d", &new->course.mark_math);
					break;
				case 3:
					printf("������Ӣ��ɼ���");
					scanf("%d", &new->course.mark_English);
					break;
				case 4:
					printf("�����뻥��������");
					scanf("%d", &new->course.mark_peer);
					break;
				case 5:
					printf("������˼��Ʒ�·�����");
					scanf("%d", &new->course.mark_morality);
					break;
				case 6:
					printf("�������ʦ���۷�����");
					scanf("%d", &new->course.mark_avg_Tch);
					break;
				}
			}

			//����ƽ���� =������+��ѧ+Ӣ�/3
			new->course.mark_avg_main_subject = (new->course.mark_Chinese + new->course.mark_math + new->course.mark_English) / 3.0;

			//�۲�ɼ� = ����ƽ���� * 0.6 + ������ * 0.1 + ˼��Ʒ�·��� * 0.1 + ��ʦ���۷��� * 0.2
			//  �õ������з���'\'
			new->course.mark_comprehensive = (new->course.mark_avg_main_subject * 0.6) + (new->course.mark_peer * 0.1) \
				+ (new->course.mark_morality * 0.1) + (new->course.mark_avg_Tch * 0.2);

			//ָ����һ���ڵ�
			new = new->next;
			setbuf(stdin, NULL);//ʹstdin��������Ĭ�ϻ�����תΪ�޻�����,�ﵽ�����������Ŀ��
			printf("�ɼ�¼��ɹ�");
			printf("\n\n");
			if (new == head)
				break;
		}
		else {
			new = new->next;
			if (new == head)
				break;
		}
		
	}

	renew_grade(head);
	printf("��ǰû����Ҫ�����ѧ���ɼ���");
	system("pause");
}

//�޸ġ����޸�ѧ����Ϣģ��
void alter_grade() {
	Student* head = initialize_table();//��ȡ����
	Student* local = head;//��¼��ͷ�ļ�����local���в���
	char num[15];//�û������ѧ��
	printf("������ѧ����ѧ�ţ�");
	scanf("%s", &num);//����ѧ��
	getchar();//���������
	for (;;) {//������ѭ������λ��ѧ��λ��
		if (strcmp(local->stu_num, num))//������Ϊ0�����������������ű�����һ��
			local = local->next;//������
		else
			break;
		if (local == head) {//�Ҳ���
			printf("�Ҳ�����ѧ���������������룡\n");
			alter_grade();
			return;//�˳�
		}
	}
	char choice;//ѡ��
	int temp;//�����Ҫ�޸�ֵ

	for (;;) {
		grade_table_head_input(local);
		printf("�����ѡ������޸ģ�a/���ĳɼ� b/��ѧ�ɼ� c/Ӣ��ɼ� d/�������� e/˼��Ʒ�·��� f/��ʦ���۷��� n/�˳��޸ģ���");
		scanf("%c", &choice);
		while (getchar() != '\n');//������л�����
		char choices[8] = "abcdefn";
		int bool = 0;
		for (int i = 0; i < 7; i++) {
			if (choice == choices[i])
				bool = 1;
		}
		if (bool == 0) {
			printf("�������ѡ���������������룡\n");
			continue;
		}

		if (choice == 'n')//nѡ���˳�
			break;

		printf("�������޸ĺ��ֵ��");
		scanf("%d", &temp);
		getchar();
		switch (choice)
		{
		case 'a':
			local->course.mark_Chinese = temp;
			break;
		case 'b':
			local->course.mark_math = temp;
			break;
		case 'c':
			local->course.mark_English = temp;
			break;
		case 'd':
			local->course.mark_peer = temp;
			break;
		case 'e':
			local->course.mark_morality = temp;
			break;
		case 'f':
			local->course.mark_avg_Tch = temp;
			break;
		default:
			break;
		}

		//���޸��˻����֡���ʦ���۷ֺ�˼��Ʒ�·֣��������۲��
		if (choice == 'd' || choice == 'e' || choice == 'f') {
			local->course.mark_comprehensive = (local->course.mark_avg_main_subject * 0.6) + (local->course.mark_peer * 0.1) \
				+ (local->course.mark_morality * 0.1) + (local->course.mark_avg_Tch * 0.2);
		}
		//���޸�������Ӣ�ĳɼ��������¼�������ƽ���ɼ���Ȼ�����¼����۲��
		else {
			local->course.mark_avg_main_subject = (local->course.mark_Chinese + local->course.mark_math + local->course.mark_English) / 3.0;
			local->course.mark_comprehensive = (local->course.mark_avg_main_subject * 0.6) + (local->course.mark_peer * 0.1) \
				+ (local->course.mark_morality * 0.1) + (local->course.mark_avg_Tch * 0.2);
		}


		renew_grade(head);//����д���ļ�

		printf("�޸ĳɹ������Ƿ���Ҫ�����޸ģ���1������������˳���");
		choice = _getch();
		if (choice != '1')
			break;
		else
			system("cls");
	}

}

//ɾ������ɾ��ѧ����Ϣģ��
void delete_grade() {
	char num[15];//�û������ѧ��
	printf("��ӭ��������ɾ��ϵͳ������ɾ�����ϲ��ⶥ������n�˳���\n");
	printf("��ܰ��ʾ�����ﲻɾ��ѧ���ļ�¼��ֻ��ѧ���ĳɼ���Ϣ���㣬��Ҫɾ��ѧ����¼���뵽ѧ�����в�����\n");

	for (;;) {//һ��ɾ��ѧ�����ݵĹ���
		Student* head = initialize_table();//��ȡ����
		Student* local = head;//��¼��ͷ�ļ�����local���в���
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

		//��ʾ��ѧ����Ϣ
		grade_table_head_input(local->next);

		printf("��ȷ���Ƿ�ɾ���� y/n ");
		char temp;
		scanf("%c", &temp);
		while (getchar() != '\n');//������л�����
		while (1) {
			if (temp == 'y' || temp == 'Y') {
				//�������еĸ�ѧ���ĳɼ�����
				local->next->course.mark_Chinese = 0;
				local->next->course.mark_math = 0;
				local->next->course.mark_English = 0;
				local->next->course.mark_avg_main_subject = 0;
				local->next->course.rank_main_subject = 0;
				local->next->course.mark_peer = 0;
				local->next->course.mark_morality = 0;
				local->next->course.mark_avg_Tch = 0;
				local->next->course.mark_comprehensive = 0;
				local->next->course.rank_comprehensive = 0;
				//����������ļ�
				renew_grade(local);//��ʱhead�Ѿ���һ����ɾ�������������
				printf("ɾ���ɹ���\n\n");
				break;
			}
			else if (temp == 'n' || temp == 'N') {
				printf("û�ж�%s��ѧ������ɾ��������\n\n", local->next->stu_num);
				break;
			}
			else {
				printf("���������� y/n �� ");
				scanf("%c", &temp);
				while (getchar() != '\n');//������л�����
			}
		}

		


		
	}
}

//��ѯ������ѯѧ����Ϣģ��
void select_grade() {
	//����Ѱ��ѧ�����ڽڵ����޸ĺ���ͬ��
	Student* head = initialize_table();//��ȡ����
	Student* local = head;//��¼��ͷ�ļ�����local���в���
	char num[15];//�û������ѧ��
	printf("�������ѧ����ѧ�ţ�");
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
			create_basic();//����ѧ������
			system("cls");//����
			select_grade();
			return;//�˳�
		}
	}



	grade_table_head_input(local);


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
	Student* head = initialize_table();
	Student* local = head;//����ͷ�ڵ�
	int col_width = 0;//�п�
	for (int i = 1;; i++) {//������ʾ���У���������������Ľڵ���������
		for (int j = 1; j < 12; j++) {//��ʾ11��

			//��ʾѧ�ź�����
			if (j == 1) {
				while (col_width < 14) {
					if (i == 1) {//��һ������������� ѧ��
						printf(" ");
						col_width++;
						if (col_width == 5 && j == 1) {//������ʾ
							col_width += printf("ѧ��");
						}
					}
					else {
						col_width += browe_center(14, strlen(local->stu_num));
						col_width += printf("%s", local->stu_num);
						col_width += browe_center(14, strlen(local->stu_num));
					}
				}
				col_width = 0;//�п�����
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ���ĳɼ�
			else if (j == 2) {
				while (col_width < 6) {
					if (i == 1) {//��һ������������� ����
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("����");
						}
					}
					else {
					/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(6, ((int)log10(local->course.mark_Chinese) + 1));
						col_width += printf("%d", local->course.mark_Chinese);
						col_width += browe_center(6, ((int)log10(local->course.mark_Chinese) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ��ѧ�ɼ�
			else if (j == 3) {
				while (col_width < 6) {
					if (i == 1) {//��һ������������� ��ѧ
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("��ѧ");
						}
					}
					else {
					/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(6, ((int)log10(local->course.mark_math) + 1));
						col_width += printf("%d", local->course.mark_math);
						col_width += browe_center(6, ((int)log10(local->course.mark_math) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾӢ��ɼ�
			else if (j == 4) {
				while (col_width < 6) {
					if (i == 1) {//��һ������������� Ӣ��
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("Ӣ��");
						};
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(6, ((int)log10(local->course.mark_English) + 1));
						col_width += printf("%d", local->course.mark_English);
						col_width += browe_center(6, ((int)log10(local->course.mark_English) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ����ƽ����
			else if (j == 5) {
				while (col_width < 12) {
					if (i == 1) {//��һ������������� ����ƽ����
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("����ƽ����");
						}
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1+3��С�������λС�������������������λ��������С���㣩*/
						col_width += browe_center(12, ((int)log10(local->course.mark_avg_main_subject) + 1 + 3));
						col_width += printf("%.2f", local->course.mark_avg_main_subject);
						col_width += browe_center(12, ((int)log10(local->course.mark_avg_main_subject) + 1 + 3));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ��������
			else if (j == 6) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� ��������
						col_width += printf("��������");
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(8, ((int)log10(local->course.rank_main_subject) + 1));
						col_width += printf("%d", local->course.rank_main_subject);
						col_width += browe_center(8, ((int)log10(local->course.rank_main_subject) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ����
			else if (j == 7) {
				while (col_width < 6) {
					if (i == 1) {//��һ������������� ����
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("����");
						}
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(6, ((int)log10(local->course.mark_peer) + 1));
						col_width += printf("%d", local->course.mark_peer);
						col_width += browe_center(6, ((int)log10(local->course.mark_peer) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ˼��Ʒ��
			else if (j == 8) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� ˼��Ʒ��
						col_width += printf("˼��Ʒ��");
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(8, ((int)log10(local->course.mark_morality) + 1));
						col_width += printf("%d", local->course.mark_morality);
						col_width += browe_center(8, ((int)log10(local->course.mark_morality) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ��ʦ����
			else if (j == 9) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� ��ʦ����
						col_width += printf("��ʦ����");
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(8, ((int)log10(local->course.mark_avg_Tch) + 1));
						col_width += printf("%d", local->course.mark_avg_Tch);
						col_width += browe_center(8, ((int)log10(local->course.mark_avg_Tch) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ�۲��
			else if (j == 10) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� �۲��
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("�۲��");
						}
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1+3��С�������λС�������������������λ��������С���㣩*/
						col_width += browe_center(8, ((int)log10(local->course.mark_comprehensive) + 1 + 3));
						col_width += printf("%.2f", local->course.mark_comprehensive);
						col_width += browe_center(8, ((int)log10(local->course.mark_comprehensive) + 1 + 3));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ�۲�����
			else if (j == 11) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� �۲�����
						col_width += printf("�۲�����");
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(8, ((int)log10(local->course.rank_comprehensive) + 1));
						col_width += printf("%d", local->course.rank_comprehensive);
						col_width += browe_center(8, ((int)log10(local->course.rank_comprehensive) + 1));
					}
				}
				col_width = 0;//�п���0
			}

		}

		printf("\n");
		//���һ�� "-" ��������Ϊ��֮��ķָ�
		while (col_width < 100) {
			//ÿ�ε���һ���п�|����λ�ú󣬸�Ϊ���һ�� "+"
			if (col_width == 14 || col_width == 21 || col_width == 28 || col_width == 35 || col_width == 48 || col_width == 57 || col_width == 64 \
				|| col_width == 73 || col_width == 82 || col_width == 91) {
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


//��д������1��
//�����ļ������������������csv�ļ����и���
void renew_grade(Student* head) {
	head = sort_link_table(head);
	//����ѧ��������ƽ�����������۲�����
	rank_main_subject(head);
	rank_comprehensive(head);
	FILE* p_ini = fopen("grade.csv", "w");
	Student* local = head;
	for (;;) {
		if (strcmp(local->stu_num, "")) {
			//д��ѧ��ѧ��
			fprintf(p_ini, "%s,", local->stu_num);
			//д�����ĳɼ�
			fprintf(p_ini, "%d,", local->course.mark_Chinese);
			//д����ѧ�ɼ�
			fprintf(p_ini, "%d,", local->course.mark_math);
			//д��Ӣ��ɼ�
			fprintf(p_ini, "%d,", local->course.mark_English);
			//д������ƽ����
			fprintf(p_ini, "%.2f,", local->course.mark_avg_main_subject);
			//д����������
			fprintf(p_ini, "%d,", local->course.rank_main_subject);
			//д�뻥������
			fprintf(p_ini, "%d,", local->course.mark_peer);
			//д��˼��Ʒ�·���
			fprintf(p_ini, "%d,", local->course.mark_morality);
			//д���ʦ���۷���
			fprintf(p_ini, "%d,", local->course.mark_avg_Tch);
			//д���۲����
			fprintf(p_ini, "%.2f,", local->course.mark_comprehensive);
			//д���۲�����
			fprintf(p_ini, "%d\n", local->course.rank_comprehensive);
			local = local->next;
		}

		if (local == head)
			break;
	}
	fclose(p_ini);
}


//�Ӻ����б�3��
//��ѯѧ����Ϣ��browse_grade�ĸ�����������select_gradeģ����ʹ�ã�������ָ��ֱ�ӽ��е��ã�����������
void grade_table_head_input(Student* head) {
	Student* local = head;//����ͷ�ڵ�
	int col_width = 0;//�п�
	for (int i = 1; i < 3; i++) {
		for (int j = 1; j < 12; j++) {//��ʾ11��

			//��ʾѧ�ź�����
			if (j == 1) {
				while (col_width < 14) {
					if (i == 1) {//��һ������������� ѧ��
						printf(" ");
						col_width++;
						if (col_width == 5 && j == 1) {//������ʾ
							col_width += printf("ѧ��");
						}
					}
					else {
						col_width += browe_center(14, strlen(local->stu_num));
						col_width += printf("%s", local->stu_num);
						col_width += browe_center(14, strlen(local->stu_num));
					}
				}
				col_width = 0;//�п�����
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ���ĳɼ�
			else if (j == 2) {
				while (col_width < 6) {
					if (i == 1) {//��һ������������� ����
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("����");
						}
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(6, ((int)log10(local->course.mark_Chinese) + 1));
						col_width += printf("%d", local->course.mark_Chinese);
						col_width += browe_center(6, ((int)log10(local->course.mark_Chinese) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ��ѧ�ɼ�
			else if (j == 3) {
				while (col_width < 6) {
					if (i == 1) {//��һ������������� ��ѧ
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("��ѧ");
						}
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(6, ((int)log10(local->course.mark_math) + 1));
						col_width += printf("%d", local->course.mark_math);
						col_width += browe_center(6, ((int)log10(local->course.mark_math) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾӢ��ɼ�
			else if (j == 4) {
				while (col_width < 6) {
					if (i == 1) {//��һ������������� Ӣ��
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("Ӣ��");
						};
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(6, ((int)log10(local->course.mark_English) + 1));
						col_width += printf("%d", local->course.mark_English);
						col_width += browe_center(6, ((int)log10(local->course.mark_English) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ����ƽ����
			else if (j == 5) {
				while (col_width < 12) {
					if (i == 1) {//��һ������������� ����ƽ����
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("����ƽ����");
						}
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1+3��С�������λС�������������������λ��������С���㣩*/
						col_width += browe_center(12, ((int)log10(local->course.mark_avg_main_subject) + 1 + 3));
						col_width += printf("%.2f", local->course.mark_avg_main_subject);
						col_width += browe_center(12, ((int)log10(local->course.mark_avg_main_subject) + 1 + 3));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ��������
			else if (j == 6) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� ��������
						col_width += printf("��������");
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(8, ((int)log10(local->course.rank_main_subject) + 1));
						col_width += printf("%d", local->course.rank_main_subject);
						col_width += browe_center(8, ((int)log10(local->course.rank_main_subject) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ����
			else if (j == 7) {
				while (col_width < 6) {
					if (i == 1) {//��һ������������� ����
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("����");
						}
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(6, ((int)log10(local->course.mark_peer) + 1));
						col_width += printf("%d", local->course.mark_peer);
						col_width += browe_center(6, ((int)log10(local->course.mark_peer) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ˼��Ʒ��
			else if (j == 8) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� ˼��Ʒ��
						col_width += printf("˼��Ʒ��");
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(8, ((int)log10(local->course.mark_morality) + 1));
						col_width += printf("%d", local->course.mark_morality);
						col_width += browe_center(8, ((int)log10(local->course.mark_morality) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ��ʦ����
			else if (j == 9) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� ��ʦ����
						col_width += printf("��ʦ����");
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(8, ((int)log10(local->course.mark_avg_Tch) + 1));
						col_width += printf("%d", local->course.mark_avg_Tch);
						col_width += browe_center(8, ((int)log10(local->course.mark_avg_Tch) + 1));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ�۲��
			else if (j == 10) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� �۲��
						printf(" ");
						col_width++;
						if (col_width == 1) {//������ʾ
							col_width += printf("�۲��");
						}
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1+3��С�������λС�������������������λ��������С���㣩*/
						col_width += browe_center(8, ((int)log10(local->course.mark_comprehensive) + 1 + 3));
						col_width += printf("%.2f", local->course.mark_comprehensive);
						col_width += browe_center(8, ((int)log10(local->course.mark_comprehensive) + 1 + 3));
					}
				}
				col_width = 0;//�п���0
				printf("|");//��Ϊ��֮��ķָ�
			}

			//��ʾ�۲�����
			else if (j == 11) {
				while (col_width < 8) {
					if (i == 1) {//��һ������������� �۲�����
						col_width += printf("�۲�����");
					}
					else {
						/*��Ҫ��ʾ����ȡ����log10��ֵ��Ȼ��ȡ�������������֣����+1�������������λ��*/
						col_width += browe_center(8, ((int)log10(local->course.rank_comprehensive) + 1));
						col_width += printf("%d", local->course.rank_comprehensive);
						col_width += browe_center(8, ((int)log10(local->course.rank_comprehensive) + 1));
					}
				}
				col_width = 0;//�п���0
			}

		}

		printf("\n");
		//���һ�� "-" ��������Ϊ��֮��ķָ�
		while (col_width < 100) {
			//ÿ�ε���һ���п�|����λ�ú󣬸�Ϊ���һ�� "+"
			if (col_width == 14 || col_width == 21 || col_width == 28 || col_width == 35 || col_width == 48 || col_width == 57 || col_width == 64 \
				|| col_width == 73 || col_width == 82 || col_width == 91) {
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

//ѧ������ƽ��������(����renew_gradeģ����ʹ��)
void rank_main_subject(Student* head) {
	Student* local = head;//����ͷ�ڵ㣬��local����
	Student* local_later = local->next;//local_laterʼ�ձ�ʾlocal����Ľڵ㣬��ʼ��Ϊlocal����һ���ڵ�
	for (;;) {
		//����ǰ��ѧ��������ƽ���ֺ��۲��Ϊ0����ʾ��ǰѧ��û��¼��ɼ������Ը�ѧ����������
		if (local->course.mark_avg_main_subject != 0 || local->course.mark_comprehensive != 0) {
			local->course.rank_main_subject = 1;//���赱ǰѧ������������Ϊ��һ��
			while (local != local_later) {//��ǰѧ��������ƽ����������������
				//����ǰѧ��������ƽ����С����һ��ѧ��������ƽ����ʱ����ǰѧ��������������1
				if (local->course.mark_avg_main_subject < local_later->course.mark_avg_main_subject) {
					local->course.rank_main_subject++;
				}
				local_later = local_later->next;//��local_laterָ����һ���ڵ�
			}
			
		}
		//��ǰѧ����������localָ���¸�ѧ����local_later����ָ��local����һ��ѧ��
		local = local->next;
		local_later = local->next;
		if (local == head) {
			break;
		}
	}
}

//ѧ���۲�����(����renew_gradeģ����ʹ��)
void rank_comprehensive(Student* head) {
	Student* local = head;//����ͷ�ڵ㣬��local����
	Student* local_later = local->next;//local_laterʼ�ձ�ʾlocal����Ľڵ㣬��ʼ��Ϊlocal����һ���ڵ�
	for (;;) {
		//����ǰ��ѧ��������ƽ���ֺ��۲��Ϊ0����ʾ��ǰѧ��û��¼��ɼ������Ը�ѧ����������
		if (local->course.mark_avg_main_subject != 0 || local->course.mark_comprehensive != 0) {
			local->course.rank_comprehensive = 1;//���赱ǰѧ�����۲�����Ϊ��һ��
			while (local != local_later) {//��ǰѧ��������ƽ����������������
				//����ǰѧ�����۲��С����һ��ѧ�����۲��ʱ����ǰѧ�����۲�������1
				if (local->course.mark_comprehensive < local_later->course.mark_comprehensive) {
					local->course.rank_comprehensive++;
				}
				local_later = local_later->next;//��local_laterָ����һ���ڵ�
			}
		
		}
		//��ǰѧ����������localָ���¸�ѧ����local_later����ָ��local����һ��ѧ��
		local = local->next;
		local_later = local->next;

		if (local == head) {
			break;
		}
	}
}








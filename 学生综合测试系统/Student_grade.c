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

	Student* head = initialize_table_grade();
	Student* new = head;
	for (;;) {
		printf("������ѧ��Ϊ��%s��ѧ���ĸ���ɼ���\n", new->stu_num);
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
		printf("\n\n");
		if (new == head)
			break;
	}

	fclose(p_ini);
	renew_grade(head);
	printf("�ɼ�¼��ɹ�!");
	system("pause");
}

//�޸ġ����޸�ѧ����Ϣģ��
void alter_grade() {
	Student* head = initialize_table_grade();//��ȡ����
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

		//���޸�������Ӣ�ĳɼ��������¼�������ƽ���ɼ�
		if (choice == 'd' || choice == 'e' || choice == 'f') {
			local->course.mark_comprehensive = (local->course.mark_avg_main_subject * 0.6) + (local->course.mark_peer * 0.1) \
				+ (local->course.mark_morality * 0.1) + (local->course.mark_avg_Tch * 0.2);
		}
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
		printf("\n\n\n");
	}

}

//ɾ������ɾ��ѧ����Ϣģ��
void delete_grade() {
	Student* head = initialize_table_grade();//��ȡ����
	Student* local = head;//��¼��ͷ�ļ�����local���в���
	char num[15];//�û������ѧ��
	printf("��ӭ��������ɾ��ϵͳ������ɾ�����ϲ��ⶥ������n�˳���\n");
	printf("��ܰ��ʾ�����ﲻɾ��ѧ���ļ�¼��ֻ��ѧ���ĳɼ���Ϣ���㣬��Ҫɾ��ѧ����¼���뵽ѧ�����в�����\n");

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

		//�������еĸ�ѧ���ĳɼ�����
		local->course.mark_Chinese = 0;
		local->course.mark_math = 0;
		local->course.mark_English = 0;
		local->course.mark_avg_main_subject = 0;
		local->course.rank_main_subject = 0;
		local->course.mark_peer = 0;
		local->course.mark_morality = 0;
		local->course.mark_avg_Tch = 0;
		local->course.mark_comprehensive = 0;
		local->course.rank_comprehensive = 0;


		//����������ļ�
		renew_grade(local);//��ʱhead�Ѿ���һ����ɾ�������������
		printf("ɾ���ɹ���\n\n");
	}
}

//��ѯ������ѯѧ����Ϣģ��


//���ѧ����Ϣ



//��д������2��
//��ȡ�������˺������ڻ�ȡ��ǰ�ļ��ڵ����ݲ�����һ���¶���������У��������򲢷��ظ������ͷָ��
Student* initialize_table_grade() {
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

	get_grade(head);//��Ŀǰ�ļ�������ݶ���������
	old = head;//��¼�µ�ǰ������ͷ��㣬�´����øú���ʱ�ͷŸýڵ�
	head = sort_link_table_grade(head);//����
	return head;//���������ͷ�ڵ�
}
//�����ļ������������������csv�ļ����и���
void renew_grade(Student* head) {
	head = sort_link_table_grade(head);
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


//�Ӻ����б�4��
//���򡪡����ļ����ݰ���ѧ�Ŵ�С�������򣨲�ֱ�ӵ��ã�
Student* sort_link_table_grade(Student* head) {
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
void get_grade(Student* head) {
	FILE* p_ini = fopen("basic.csv", "r");//����ʽ���ļ�
	FILE* p_init = fopen("grade.csv", "r");
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

		char temp_t[30] = {"\0"};
		fscanf(p_init, "%[^,],", temp_t);//��grade.csv�ļ���ĵ�һ��ѧ�Ŷ������������������У���һ��ռλ�����ã�
		fscanf(p_init, "%d,", &p->course.mark_Chinese);//��ȡ���ĳɼ�
		fscanf(p_init, "%d,", &p->course.mark_math);//��ȡ��ѧ�ɼ�
		fscanf(p_init, "%d,", &p->course.mark_English);//��ȡӢ��ɼ�
		fscanf(p_init, "%f,", &p->course.mark_avg_main_subject);//��ȡ����ƽ����
		fscanf(p_init, "%d,", &p->course.rank_main_subject);//��ȡ��������
		fscanf(p_init, "%d,", &p->course.mark_peer);//��ȡ��ƴ��
		fscanf(p_init, "%d,", &p->course.mark_morality);//��ȡ˼��Ʒ�·���
		fscanf(p_init, "%d,", &p->course.mark_avg_Tch);//��ȡ��ʦ���۷���
		fscanf(p_init, "%f,", &p->course.mark_comprehensive);//��ȡ�۲����
		fscanf(p_init, "%d\n", &p->course.rank_comprehensive);//��ȡ�۲�����

		

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


//��ѯѧ����Ϣ��browse_data�ĸ�����������select_basicģ����ʹ�ã�������ָ��ֱ�ӽ��е��ã�����������








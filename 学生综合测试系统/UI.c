#include "config.h"
#include "UI.h"
#include <tchar.h>
int flag = 0;//UI����ı�־λ

void UI_main() {
	system("cls");//����ָ��
	printf("                                       ѧ �� �� �� �� �� ϵ ͳ                                       ");
	printf("\n");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                                                                                                  *");
	printf("*                                       1 �� �� ѧ �� �� Ϣ ��                                     *");
	printf("*                                                                                                  *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                                                                                                  *");
	printf("*                                       2 �� �� ѧ �� �� �� ��                                     *");
	printf("*                                                                                                  *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                                                                                                  *");
	printf("*                                      -1 �� �� ϵ ͳ                                              *");
	printf("*                                                                                                  *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("�������Ӧ�����֣�ִ�й��ܣ�");
	scanf("%d", &flag);
	getchar();//����scanf����ʱ�Ļس���
}

void UI_students() {
	system("cls");//����ָ��
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                                  1 �� �� ѧ �� �� ��                                             *");
	printf("*                                  2 �� �� ѧ �� �� ��                                             *");
	printf("*                                  3 ɾ �� ѧ �� �� ��                                             *");
	printf("*                                  4 � �� ѧ �� �� ��                                             *");
	printf("*                                  5 �� ѯ ѧ �� �� ��                                             *");
	printf("*                                  0 �� �� �� �� ��                                                *");
	printf("*                                 -1 �� �� ϵ ͳ                                                   *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("�������Ӧ�����֣�ִ�й��ܣ�");
	scanf("%d", &flag);
	getchar();//����scanf����ʱ�Ļس���
	switch (flag) {
	case 1://����ѧ������
		system("cls");//����ָ��
		while (1) {
			create_basic();
			printf("д��ɹ����Ƿ��������? (y or n)");
			char temp;//�м���������������y��n
			while (1) {
				temp = getchar();
				char c;//����������õ��м����
				while ((c = getchar()) != '\n');//�����������ֱ��cΪ\nʱ�Ž���
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("������ y or n:");
			}
			if (temp == 'n' || temp == 'N') {//�˳�whileѭ�������ص�ѧ����Ϣ�����
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//����ѭ������������ѧ����Ϣ
				continue;
			}
		}
		break;
	case 2://�޸�ѧ������
		system("cls");//����ָ��
		while (1) {
			/*     ����    */
			printf("�޸ĳɹ����Ƿ�����޸�? (y or n)");
			char temp;//�м���������������y��n
			while (1) {
				temp = getchar();
				char c;//����������õ��м����
				while ((c = getchar()) != '\n');//�����������ֱ��cΪ\nʱ�Ž���
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("������ y or n:");
			}
			if (temp == 'n' || temp == 'N') {//�˳�whileѭ�������ص�ѧ����Ϣ�����
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//����ѭ������������ѧ����Ϣ
				continue;
			}
		}
		break;
	case 3://ɾ��ѧ������
		system("cls");//����ָ��
		while (1) {
			/*     ����    */
			printf("ɾ���ɹ����Ƿ����ɾ��? (y or n)");
			char temp;//�м���������������y��n
			while (1) {
				temp = getchar();
				char c;//����������õ��м����
				while ((c = getchar()) != '\n');//�����������ֱ��cΪ\nʱ�Ž���
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("������ y or n:");
			}
			if (temp == 'n' || temp == 'N') {//�˳�whileѭ�������ص�ѧ����Ϣ�����
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//����ѭ������������ѧ����Ϣ
				continue;
			}
		}
		break;
	case 4://���ѧ����Ϣ
		system("cls");//����ָ��
		/*   ����   */
		break;
	case 5://��ѯѧ����Ϣ
		system("cls");//����ָ��
		while (1) {
			/*     ����    */
			printf("��ѯ�ɹ����Ƿ������ѯ? (y or n)");
			char temp;//�м���������������y��n
			while (1) {
				temp = getchar();
				char c;//����������õ��м����
				while ((c = getchar()) != '\n');//�����������ֱ��cΪ\nʱ�Ž���
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("������ y or n:");
			}
			if (temp == 'n' || temp == 'N') {//�˳�whileѭ�������ص�ѧ����Ϣ�����
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//����ѭ������������ѧ����Ϣ
				continue;
			}
		}
		break;
	}
}

void UI_grade() {
	system("cls");//����ָ��
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("*                               1 �� �� ѧ �� �� Ŀ �� ��                                          *");
	printf("*                               2 �� �� ѧ �� �� �� �� ��                                          *");
	printf("*                               0 �� �� �� �� ��                                                   *");
	printf("*                              -1 �� �� ϵ ͳ                                                      *");
	printf("*--------------------------------------------------------------------------------------------------*");
	printf("�������Ӧ�����֣�ִ�й��ܣ�");
	scanf("%d", &flag);
	getchar();//����scanf����ʱ�Ļس���
	switch (flag) {
	case 1:
		while (1) {
			/*    ����    */
			printf("д��ɹ����Ƿ����д��? (y or n)");
			char temp;//�м���������������y��n
			while (1) {
				temp = getchar();
				char c;//����������õ��м����
				while ((c = getchar()) != '\n');//�����������ֱ��cΪ\nʱ�Ž���
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("������ y or n:");
			}
			if (temp == 'n' || temp == 'N') {//�˳�whileѭ�������ص�ѧ����Ϣ�����
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//����ѭ������������ѧ����Ϣ
				continue;
			}
		}
		break;
	case 2:
		while (1) {
			/*    ����    */
			printf("д��ɹ����Ƿ��������? (y or n)");
			char temp;//�м���������������y��n
			while (1) {
				temp = getchar();
				char c;//����������õ��м����
				while ((c = getchar()) != '\n');//�����������ֱ��cΪ\nʱ�Ž���
				if (temp == 'y' || temp == 'Y' || temp == 'n' || temp == 'N') {
					break;
				}
				printf("������ y or n:");
			}
			if (temp == 'n' || temp == 'N') {//�˳�whileѭ�������ص�ѧ����Ϣ�����
				break;
			}
			else if (temp == 'y' || temp == 'Y') {//����ѭ������������ѧ����Ϣ
				continue;
			}
		}
		break;
	}
}

//���ÿ���̨��λ��
void gotoxy(short x, short y) {
	COORD coord = { x, y };//COORD��Windows API�ж����һ�ֽṹ�����ͣ���ʾ����̨��Ļ�ϵ����ꡣ���β�x��y���г�ʼ����
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);//���ÿ���̨���λ��
	//GetStdHandle(STD_OUTPUT_HANDLE); ��ȡ����̨������
}

void UI() {
	SetConsoleTitle(_T("ѧ���ۺϲ���ϵͳOVO"));//���Ĵ��ڵı���
	system("mode con: cols=100 lines=50");//���Ĵ��ڵĴ�С
	while (flag != -1) {
		if (flag == 0) {
			UI_main();
		}
		else if (flag == 1) {
			UI_students();
		}
		else if (flag == 2) {
			UI_grade();
		}
		else if (flag == -1) {
			system("exit");//�ر�Dos���ڣ��˳�����
		}
	}
}
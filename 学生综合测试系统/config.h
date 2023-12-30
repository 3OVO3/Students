#ifndef __CONFIG_H__
#define __CONFIG_H__
#define _CRT_SECURE_NO_WARNINGS 1

//����ѧ���ɼ��Ľṹ��
//��typedef ���Ը��ṹ���ñ������������ÿ���ʡ��struct��
typedef struct Course {
	int mark_Chinese;//���ķ���
	int mark_math;//��ѧ����
	int mark_English;//Ӣ�����
	float mark_avg_main_subject;//����ƽ����
	int rank_main_subject;//��������
	int mark_peer;//��������
	int mark_morality;//˼��Ʒ�·���
	int mark_avg_Tch;//ƽ����ʦ���۷���
	float mark_comprehensive;//�۲����
	int rank_comprehensive;//�۲�����
}Course;


//����ѧ��������Ϣ�Ľṹ��
typedef struct Student {
	char stu_num[15];//ѧ��
	char stu_name[20];//����
	char stu_sex[10];//�Ա�
	char stu_address[30];//��ͥסַ
	char stu_phone_num[30];//��ϵ�绰
	struct Student* next;//����������Ĵ���
	struct Course course;//������������Course��
}Student;





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include <conio.h>
#include "UI.h"
#include "Student_data.h"
#include "Student_grade.h"
#endif

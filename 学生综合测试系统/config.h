#ifndef __CONFIG_H__
#define __CONFIG_H__
#define _CRT_SECURE_NO_WARNINGS 1

//定义学生基本信息的结构体
//（typedef 可以给结构体用别名，后续调用可以省略struct）
typedef struct Student {
	char stu_num[15];//学号
	char stu_name[20];//姓名
	char stu_sex[10];//性别
	char stu_address[30];//家庭住址
	char stu_phone_num[30];//联系电话
	struct Student* next;//用于链表结点的串连
	struct Course* course_data;//纵向串联学生成绩的链表
}Student;


//定义学生成绩的结构体
typedef struct Course {
	int mark_Chinese;//语文分数
	int mark_math;//数学分数
	int mark_English;//英语分数
	int mark_avg_main_subject;//主科平均分
	int rank_main_subject;//主科排名
	int mark_peer;//互评分数
	int mark_morality;//思想品德分数
	int mark_avg_Tch;//平均教师评价分数
	int mark_comprehensive;//综测分数
	int rank_comprehensive;//综测名次
}Course;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> 
#include "UI.h"
#include "Student_data.h"
#endif

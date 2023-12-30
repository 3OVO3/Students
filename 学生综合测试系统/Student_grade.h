#ifndef __STUDENT_GRADE_H__
#define __STUDENT_GRADE_H__

#include <math.h>

//功能函数【5】
void create_grade();
void alter_grade();
void delete_grade();
void select_grade();
void browse_grade();
//读写函数【1】
void renew_grade(Student* head);
//子函数【3】
void grade_table_head_input(Student* head);
void rank_main_subject(Student* head);
void rank_comprehensive(Student* head);

#endif

#ifndef __STUDENT_GRADE_H__
#define __STUDENT_GRADE_H__

#include <math.h>

//功能函数【5】
void create_grade();
void alter_grade();
void delete_grade();
//void select_grade();
//void browse_grade();
//读写函数【2】
Student* initialize_table_grade();
void renew_grade(Student* head);
//子函数【5】
Student* sort_link_table_grade(Student* head);
void get_grade(Student* head);
//int browe_center_grade(int col_width, int len);
//void table_head_input_grade(Student* head);


#endif

#ifndef __STUDENT_DATA_H__
#define __STUDENT_DATA_H__

#include <conio.h>//����_getch()������ͷ�ļ������ڱ�������ʹ��

//���ܺ�����5��
void create_basic();
void alter_basic();
void delete_basic();
void select_basic();
void browse_data();

//��д������2��
Student* initialize_table();
void renew_data(Student* head);

//�Ӻ�����4��
Student* sort_link_table(Student* head);
void get_data(Student* head);
int browe_center(int col_width, int len);
void table_head_input(Student* head);

#endif // !__STUDENT_DATAs_H__



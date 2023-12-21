#include "config.h"

int main() {
	//UI();
	Student* p = initialize_table();
	Student* head = p;//��¼��ͷָ��
	get_data(p);
	while (1) {
		printf("%s %s %s %s %s\n", p->stu_num, p->stu_name, p->stu_sex, p->stu_address, p->stu_phone_num);
		p = p->next;
		if (p == head)
			break;
	}
}
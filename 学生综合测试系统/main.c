#define _CRT_SECURE_NO_WARNINGS 1
#include "config.h"

int main() {
	int n;
	while (1) {
		UI();
		scanf("%d", &n);
		if (n == 0) {
			break;
		}
	}

	return 0;
}
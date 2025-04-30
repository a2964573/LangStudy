#include "main.h"

int len(char* p)
{
	int len = 0;

	while(*p != '\0') {
		len++;
	}

	return len;
}

int main()
{
	char* p1 = "2025";
	char* p2 = "202504";

	int a = atoi(p1);
	int b = atoi(p2);

	printf("%d\n", len((char*)a) + len((char*)b));
}


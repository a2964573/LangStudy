#include "main.h"

FILE* test_popen(char* command)
{
    FILE* fptr = popen(command, "r");
    if(fptr == NULL) {
        printf("popen failed. [%d:%s]\n", strlen(command), command);
    }

	return fptr;
}

int main(int argc, char* argv[])
{
	if(argc < 2) {
		printf("invalid argument...\n");
		return -1;
	}

	char* command = argv[1];
	char  result[4096 + 1];
	memset(result, 0x00, sizeof(result));

	FILE* file_ptr = test_popen(command);
	if(file_ptr == NULL) {
		pclose(file_ptr);
		return -1;
	}

	while(fgets(result, sizeof(result), file_ptr) != NULL) {
		printf("result %.4d:%s", strlen(result), result);
	}

	pclose(file_ptr);


	return 0;
}


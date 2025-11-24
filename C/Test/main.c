#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
/*
	int opt;
	while(1) {
		opt = getopt(argc, argv, "c:");
		if(opt == -1) {
			printf("EOF\n");
			break;
		}

		switch(opt) {
			case 'c':
				printf("[%s]\n", optarg);
			break;
			case '?':
				printf("input argument is NULL\n");
			break;
			default:
				printf("not invalid option\n");
				return -1;
		}
	}
*/
	printf("%s\n", (char*)20241223);

    return 0;
}


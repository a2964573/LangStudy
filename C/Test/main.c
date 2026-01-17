#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


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
//	printf("%s\n", (char*)20241223);

//	int left = atoi(argv[1]);
//	int right = atoi(argv[2]);

//	printf("%d\n", left + (right - left) / 2);
//	printf("%d\n", (left + right) / 2);
/*
	printf("# %d %d\n", left, right);
	printf("$ %d\n", left * right);

	int base;
	int temp = left < right ? right : left;
	if(temp <= 10) {
		base = 10;
	}
	else
	if(temp <= 100) {
		base = 100;
	}
	else
	if(temp <= 1000) {
		base = 1000;
	}
	else {
		return -1;
	}

	int l_sub = left - base;
	int r_sub = right - base;

	int bigger = (left + r_sub) * base;
	int smaller = l_sub * r_sub;

	printf("$ %d\n", bigger + smaller);
*/

	#define EXCHID_HKS 12
	#define EXCHID_SZS 13
	#define EXCHID_SHS 14
	#define EXCHID_NYS 15
	#define EXCHID_AMX 16
	#define EXCHID_NAS 17
	#define EXCHID_KRX 22
	#define EXCHID_AU_ 31
	#define EXCHID_HWA 32
	#define EXCHID_LA_ 34

	printf("# test\n");

	long value = strtol(argv[1], NULL, 16);
	long mask_hks = (1L << EXCHID_HKS);
	long mask_szs = (1L << EXCHID_SZS);
	long mask_shs = (1L << EXCHID_SHS);
	long mask_nys = (1L << EXCHID_NYS);
	long mask_amx = (1L << EXCHID_AMX);
	long mask_nas = (1L << EXCHID_NAS);
	long mask_krx = (1L << EXCHID_KRX);
	long mask_au_ = (1L << EXCHID_AU_);
	long mask_hwa = (1L << EXCHID_HWA);
	long mask_la_ = (1L << EXCHID_LA_);

	if(value & mask_hks) {
		printf("  HKS: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_HKS, mask_hks);
	}

	if(value & mask_szs) {
		printf("  SZS: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_SZS, mask_szs);
	}

	if(value & mask_shs) {
		printf("  SHS: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_SHS, mask_shs);
	}

	if(value & mask_nys) {
		printf("  NYS: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_NYS, mask_nys);
	}

	if(value & mask_amx) {
		printf("  AMX: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_AMX, mask_amx);
	}

	if(value & mask_nas) {
		printf("  NAS: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_NAS, mask_nas);
	}

	if(value & mask_krx) {
		printf("  KRX: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_KRX, mask_krx);
	}

	if(value & mask_au_) {
		printf("  AU_: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_AU_, mask_au_);
	}

	if(value & mask_hwa) {
		printf("  HWA: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_HWA, mask_hwa);
	}

	if(value & mask_la_) {
		printf("  LA_: %s:%ld (0x%lx):%d (0x%lx)\n", argv[1], value, value, EXCHID_LA_, mask_la_);
	}

    return 0;
}


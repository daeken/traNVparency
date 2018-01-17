#include "nvwrapper.h"

void hexdump(unsigned char *data, int size) {
	for(int i = 0; i < size; i += 16) {
		printf("%04x | ", i);
		for(int j = 0; j < 16; ++j) {
			if(i + j >= size)
				printf("   ");
			else
				printf("%02x ", data[i + j]);
			if(j == 7)
				printf(" ");
		}
		printf("\n");
	}
	printf("%04x\n", size);
}

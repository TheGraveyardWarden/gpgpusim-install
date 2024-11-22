#ifndef _RAND_STR_H_
#define _RAND_STR_H_

#include <time.h>
#include <stdlib.h>

static char alphabets[] = {'a', 'A', 'b', 'B', 'c', 'C', 'd', 'D', 'e', 'E', 'f', 'F','g', 'G', 'h', 'H', 'i', 'I',
	                      'j', 'J', 'k', 'K', 'l', 'L', 'm', 'M', 'n', 'N', 'o', 'O', 'p', 'P', 'q', 'Q', 'r', 'R',
						  's', 'S', 't', 'T', 'u', 'U', 'v', 'V', 'w', 'W', 'x', 'X', 'y', 'Y', 'z', 'Z'};

void rand_str(char *dst, int n) {
	int i;

	srand(time(NULL));
	
	for (i = 0; i < n-1; i++) {
		dst[i] = alphabets[rand()%52];
	}
	
	dst[n] = 0;
}

#endif

#ifndef GAS_QSORT_H
#define GAS_QSORT_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Swaps the block of memory at a with the memory
// at b of size size
void swap(void* a, void* b, size_t size){
	char* s = (char*)a;
	char* t = (char*)b;

	for(size_t m=0; m<size; m++){
		char tmp = s[m];
		s[m] = t[m];
		t[m] = tmp;
	}
}

void printbaseasint(int* base, size_t num){
	printf("(");
	for(size_t i=0; i<num; i++){
		printf("%d,",base[i]);
	}
	printf(")\n");
}

double alpha = 0.0;
int choosepiv_PIV_ALPHA(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	return (int)(alpha * (double)num);
}

int choosepiv_PIV_RANDOM(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	return rand() % num;
}

int k=0;
int choosepiv_PIV_LINEAR(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	return (++k) % num;
}

int choosepiv_PIV_QUADRATIC(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	k++;
	return (k*k) % num;
}

int choosepiv_PIV_TRICK_1(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	if(num > 1){
		compar(base,base+size);
		return 0;
	}else{
		return 0;
	}
}

int C = 3;

int choosepiv_PIV_TRICK_2(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	for(int i=0; i<C; i++){
		compar(base + (rand() % num)*size, base + (rand() % num)*size);
	}
	return 0;
}

int choosepiv_DEFAULT(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	return 0;
}

#define PIV_DEFAULT 0
#define PIV_ALPHA 1
#define PIV_RANDOM 2
#define PIV_LINEAR 3
#define PIV_QUADRATIC 4
#define PIV_TRICK_1 5
#define PIV_TRICK_2 6

int piv_mode=PIV_DEFAULT;

int choosepiv(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	switch(piv_mode){
		case PIV_ALPHA:
			return choosepiv_PIV_ALPHA(base,num,size,compar);
		case PIV_RANDOM:
			return choosepiv_PIV_RANDOM(base,num,size,compar);
		case PIV_LINEAR:
			return choosepiv_PIV_LINEAR(base,num,size,compar);
		case PIV_QUADRATIC:
			return choosepiv_PIV_QUADRATIC(base,num,size,compar);
		case PIV_TRICK_1:
			return choosepiv_PIV_TRICK_1(base,num,size,compar);
		case PIV_TRICK_2:
			return choosepiv_PIV_TRICK_2(base,num,size,compar);
		default:
			return choosepiv_DEFAULT(base,num,size,compar);
	}
}

int setmode(char* modename){
	if(strcmp("PIV_DEFAULT",modename) == 0) return piv_mode = PIV_DEFAULT;
	if(strcmp("PIV_ALPHA",modename) == 0) return piv_mode = PIV_ALPHA;
	if(strcmp("PIV_RANDOM",modename) == 0) return piv_mode = PIV_RANDOM;
	if(strcmp("PIV_LINEAR",modename) == 0) return piv_mode = PIV_LINEAR;
	if(strcmp("PIV_QUADRATIC",modename) == 0) return piv_mode = PIV_QUADRATIC;
	if(strcmp("PIV_TRICK_1",modename) == 0) return piv_mode = PIV_TRICK_1;
	if(strcmp("PIV_TRICK_2",modename) == 0) return piv_mode = PIV_TRICK_2;

	printf("gas_sort: %s is not a recognized mode name\n",modename);
	exit(1);
}



// Returns j such that
// |    < p    | p |     >= p    |
//  0           j   j+1           num
int partition(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	int k = choosepiv(base,num,size,compar);

	swap(base,base+k*size,size);

	int i;
	int j = 1;
	for(i=1;i<num;i++){
		if(compar(base+i*size,base) < 0){
			swap(base + j*size, base + i*size, size);
			j++;
		}
	}

	swap(base,base + (j-1)*size,size);

	return j-1;
}

void gas_qsort(void* base, size_t num, size_t size, int (*compar)(const void*, const void*)){
	if(num < 2) return;

	int r = partition(base, num, size, compar);

	gas_qsort(base,r,size,compar);
	gas_qsort(base + (r+1)*size,num - r - 1,size,compar);
}


#endif

#include "gas_qsort.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef USE_QSORT
#define qsort gas_qsort
#endif
#include "aqsort.h"



int int_cmp(const void* a, const void* b){
	if(*(int*)a < *(int*)b) return -1;
	if(*(int*)a > *(int*)b) return 1;
	return 0;
}

int main(int argc, char **argv){
	int n;
	int* b;

	srand(190);

	if(argc == 1){
		fprintf(stderr,"usage: gas_qsort n [mode] [-p]\n");
		exit(1);
	}
	n = atoi(argv[1]);
	b = malloc(n*sizeof(int));
	if(b == 0) {
		fprintf(stderr,"gas_qsort: out of space\n");
		exit(1);
	}

#ifndef USE_QSORT
	if(argc > 2){
		setmode(argv[2]);
	}

	int info = 1;
	if(argc > 4 && strcmp(argv[4],"-d") == 0) info = 0;

	if(strcmp(argv[2],"PIV_ALPHA") == 0){
		for(alpha=0.0; alpha <= 1.0; alpha += 0.01){
			int ncmp = aqsort(n, b);
			if(info) printf("alpha=%f n=%d count=%d\n",alpha, n, ncmp);
		}
	}else if(strcmp(argv[2],"PIV_TRICK_2") == 0){
		for(C=0;C<4;C++){
			int ncmp = aqsort(n, b);
			if(info) printf("C=%d n=%d count=%d\n",C, n, ncmp);
		}
	}else{
		int ncmp = aqsort(n, b);
		if(info) printf("n=%d count=%d\n", n, ncmp);
	}

	if(argc > 3 && strcmp(argv[3],"-p") == 0){ 
		for(int i=0; i<n; i++){
			printf("%d\n",b[i]);
		}
	}
#else
	int ncmp = aqsort(n, b);
	printf("n=%d count=%d\n", n, ncmp);

	if(argc > 2 && strcmp(argv[2],"-p") == 0){ 
		for(int i=0; i<n; i++){
			printf("%d\n",b[i]);
		}
	}
#endif

	exit(0);
}
/*
 * Hugmyndir:
 *    - Skoða áhrif alpha * num pivot vals þar sem við skoðum mismunandi alpha
 *        og geta alpha vs fjöldi samanburða plot
 *    - Skoða handahófs val
 *    - Skoða reglulegt val af einhverju tagi
 *    - Histogram af random fylkjum og fjölda samanburða
 *    - Sýna myndir af fylkjunum sem aqsort gefur
 */

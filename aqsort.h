#ifndef AQSORT_H
#define AQSORT_H

#include <assert.h>
int	*val;			/* array, solidified on the fly */
int	ncmp;			/* number of comparisons */
int	nsolid;			/* number of solid items */
int	candidate;		/* pivot candidate */
int	gas;			/* gas value = highest sorted value */
#define freeze(x) val[x] = nsolid++

int N;

int
cmp(const void *px, const void *py)  /* per C standard */
{
	const int x = *(const int*)px;
	const int y = *(const int*)py;
	ncmp++;
	if(val[x]==gas && val[y]==gas)
		if(x == candidate)
			freeze(x);
		else
			freeze(y);
	if(val[x] == gas)
		candidate = x;
	else if(val[y] == gas)
		candidate = y;

	return val[x] - val[y];
}

int
aqsort(int n, int* a)
{
	int i;
	int *ptr = malloc(n*sizeof(*ptr));
	val = a;
	gas = n-1;
	nsolid = ncmp = candidate = 0;
	for(i=0; i<n; i++) {
		ptr[i] = i;
		val[i] = gas;
	}
	qsort(ptr, n, sizeof(*ptr), cmp);
	for(i=1;i<n;i++)
		assert(val[ptr[i]]==val[ptr[i-1]]+1);
	free(ptr);
	return ncmp;
}


#endif

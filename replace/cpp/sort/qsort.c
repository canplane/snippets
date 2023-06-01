/* 
 * Quicksort (randomized, LR ptrs)
 * ----------------
 * Sanghoon Lee (canplane@gmail.com)
 * 2023-05-22
 */


/*

	#define			T										char *
	T A[1001];
	int _cmp(const void *a, const void *b) { return strcmp(*(T *)a, *(T *)b); }
	qsort(A, n, sizeof(*A), _cmp);


	#define			sort(begin, end, cmp)					qsort((begin), (end) - (begin), sizeof(*(begin)), (cmp))

 */


#include		<stdlib.h>
#include		<time.h>

#define			SWAP(x, y, t)							((t) = (x), (x) = (y), (y) = (t))




#define			T										int

void sort(T *l, T *r) {									// [l, r)
	T t;
	if (l == r)		return;
	T pi = *(l + rand() % (r - l));
	T *i = l - 1, *j = r;
	while (1) {
		while (*++i < pi);
		while (*--j > pi);
		if (i < j)		SWAP(*i, *j, t);
		else			break;
	}
	// i == j OR i == j + 1
	sort(l, i);
	sort(j + 1, r);
}

void nth_element(T *l, T *nth, T *r) {					// [l, r)
	T t;
	if (l == r)		return;

	T pi = *(l + rand() % (r - l));
	T *i = l - 1, *j = r;
	while (1) {
		while (*++i < pi);
		while (*--j > pi);
		if (i < j)		SWAP(*i, *j, t);
		else			break;
	}
	// i == j OR i == j + 1
	if (nth < i)	nth_element(l, nth, i);
	else			nth_element(j + 1, nth, r);
}




/** ver 2 : 조건문 2N번 (위의 것은 N번) -> 더 느림 */
/* LL ptrs */
/*
void sort(T *l, T *r) {
	T t;
	if (l == r)		return;

	T *pi = l + rand() % (r - l);
	SWAP(*pi, *l, t);
 
	T *i = l, *j;
	for (j = l + 1; j < r; j++) {
		if (*j <= *l)	++i, SWAP(*j, *i, t);
	}
	SWAP(*l, *i, t);

	sort(l, i);
	sort(i + 1, r);
}*/
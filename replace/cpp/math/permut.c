#include		<stdio.h>

#define			SWAP(x, y, t)		((t) = (x), (x) = (y), (y) = (t))

/*
	next_permutation()처럼 오름차순으로 출력해주진 않는다.
	중복 값 존재할 때도 가지치기 못함.
 */
int _p[10];
void permut(int n, int r, int pos)
{
	if (pos == r) {
		for (int i = 0; i < r; i++)		printf("%d ", _p[i]);
		printf("\n");
		return;
	}

	int t;
	for (int i = pos; i < n; i++) {
		SWAP(_p[pos], _p[i], t);
		permut(n, r, pos + 1);
		SWAP(_p[pos], _p[i], t);
	}
}

int main()
{
	int n = 4, r = 2;
	for (int i = 0; i < n; i++)		_p[i] = i + 1;

	permut(n, r, 0);
}
#include		<stdio.h>

#define			SWAP(x, y, t)		((t) = (x), (x) = (y), (y) = (t))

/*
	next_permutation()처럼 오름차순으로 출력해주진 않는다.
	중복 값 존재할 때도 가지치기 못함.
 */
int perm[10], n, r;
void permut(int r_i)
{
	if (r_i == r) {
		for (int i = 0; i < r; i++)
			printf("%d ", perm[i]);
		printf("\n");
		return;
	}

	int t;
	for (int i = r_i; i < n; i++) {
		SWAP(perm[r_i], perm[i], t);
		permut(r_i + 1);
		SWAP(perm[r_i], perm[i], t);
	}
}

int main()
{
	n = 4, r = 2;
	for (int i = 0; i < n; i++)
		perm[i] = i + 1;

	permut(0);
}
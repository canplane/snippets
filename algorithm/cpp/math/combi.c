#include		<stdio.h>

int comb[10], n, r;
void combi(int n_i, int r_i)
{
	if (r_i == r) {
		for (int i = 0; i < r; i++) printf("%d ", comb[i]);
		puts("");
		return;
	}
	for (int i = n_i; i < n; i++) {
		comb[r_i] = i + 1, combi(i + 1, r_i + 1);
	}
}

int main()
{
	n = 4, r = 2;
	
	combi(0, 0);
}
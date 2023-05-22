#include		<stdio.h>

int _c[10];
void combi(int n, int r, int n_left, int pos)
{
	if (pos == r) {
		for (int i = 0; i < r; i++) printf("%d ", _c[i]);
		puts("");
		return;
	}
	if (n_left == n)  return;

	for (int i = n_left; i < n; i++) {
		_c[pos] = i + 1;
		combi(n, r, i + 1, pos + 1);
	}
}

int main()
{
	int n = 4, r = 2;

	combi(n, r, 0, 0);
}
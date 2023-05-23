#include	<stdio.h>

#define		MAX_N		100000
int seg[1 + 4 * MAX_N], seg_idx[1 + MAX_N];
int seg_init(int l, int r, int i)
{
	if (l == r) {
		seg_idx[l] = i;
		return seg[i] = 1;
	}

	int m = (l + r) / 2;
	return seg[i] = seg_init(l, m, 2 * i) + seg_init(m + 1, r, 2 * i + 1);
}
int seg_query(int l, int r, int i, int key)			// key -> sum
{
	if (l == r)
		return seg[i];

	int m = (l + r) / 2;
	if (key <= m)
		return seg_query(l, m, 2 * i, key);
	else
		return seg[2 * i] + seg_query(m + 1, r, 2 * i + 1, key);
}
int seg_inv_query(int l, int r, int i, int sum)		// sum -> key
{
	if (l == r)
		return l;

	int m = (l + r) / 2;
	if (sum <= seg[2 * i])
		return seg_inv_query(l, m, 2 * i, sum);
	else
		return seg_inv_query(m + 1, r, 2 * i + 1, sum - seg[2 * i]);
}




/* example: BOJ 1168 on 2023-05-23 */

void seg_update(int i)
{
	for (; i > 0; i /= 2)
		seg[i]--;
}

int main()
{
	int N, K;
	scanf("%d %d", &N, &K);

	seg_init(1, N, 1);
	int sum = seg[1], key;
	
	key = seg_inv_query(1, N, 1, sum = 1 + ((sum + K) - 1) % seg[1]);
	printf("<%d", key);
	seg_update(seg_idx[key]), sum--;
	while (seg[1] > 0) {
		key = seg_inv_query(1, N, 1, sum = 1 + ((sum + K) - 1) % seg[1]);
		seg_update(seg_idx[key]), sum--;
		printf(", %d", key);
	}
	printf(">");
}
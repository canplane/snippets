#define DJ_SZ 1000
int parent[DJ_SZ];

void dj_init()
{
	for (int i = 0; i < DJ_SZ; i++)
		parent[i] = i;
}

int dj_find(int x)
{
	int r = x;
	while (parent[r] != r)
		r = parent[r];
	
	while (parent[x] != x) {
		int t = x;
		x = parent[x];
		parent[t] = r;
	}
	return r;
}
void dj_union(int x, int y)
{
	int rx = dj_find(x), ry = dj_find(y);
	parent[ry] = x;
}

bool is_root[DJ_SZ];
int dj_size()
{
	for (int i = 0; i < DJ_SZ; i++)
		is_root[dj_find(i)] = true;
	
	int ret = 0;
	for (int i = 0; i < DJ_SZ; i++)
		ret += is_root[i];
	return ret;
}
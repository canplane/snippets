#define DJ_SZ 1000
int parent[DJ_SZ];

void dj_init()
{
	for (int v = 0; v < DJ_SZ; v++) {
		parent[v] = v;
	}
}
int dj_find(int v)
{
	int r = v;
	while (parent[r] != r) {
		r = parent[r];
	}
	int t;
	while ((t = parent[v]) != v) {
		parent[v] = r;
		v = t;
	}
	return r;
}
void dj_union(int u, int v)
{
	int ru = dj_find(u), rv = dj_find(v);
	parent[rv] = ru;
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
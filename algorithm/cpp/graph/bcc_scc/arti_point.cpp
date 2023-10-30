// BOJ 11266
// 단절점, 단절선은 무방향 그래프의 용어! (방향 그래프에서는 SCC 아닐까?)

using namespace std;
#include <bits/stdc++.h>

int V, E;
vector<int> adj[10001];

vector<int> artis;

int dfn[10001], max_dfn;
int bicon(int v, int u)
{
	bool arti = false;
	int nc = 0;	// used if root
	int low = (dfn[v] = ++max_dfn), low_w;
	for (int w : adj[v]) {
		if (w == u) {
			continue;
		}
		if (!dfn[w]) {
			++nc, low_w = bicon(w, v);
			// low[v] = min(dfn[v], low[w] (child), dfn[w] (back edge))
			if (u && dfn[v] <= low_w) {	// detection: dfn(v) <= low(w) (if v is not root, w is a child)
				arti = true;
			}
		}
		else {	// back edge (because this is undirected graph)
			low_w = dfn[w];
		}
		low = min(low, low_w);
	}
	if (!u && nc > 1) {	// detection: if has more than a child (if v is root)
		arti = true;
	}
	if (arti) {
		artis.push_back(v);
	}
	return low;
}

int main()
{
	scanf("%d %d", &V, &E);
	while (E--) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b), adj[b].push_back(a);
	}

	for (int v = 1; v <= V; v++) {
		if (!dfn[v]) {
			bicon(v, 0);
		}
	}
	sort(begin(artis), end(artis));

	printf("%ld\n", artis.size());
	for (int v : artis) {
		printf("%d ", v);
	}
}
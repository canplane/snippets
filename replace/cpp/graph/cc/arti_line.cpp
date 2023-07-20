// BOJ 11400
// 단절점, 단절선은 무방향 그래프의 용어! (방향 그래프에서는 SCC 아닐까?)

using namespace std;
#include <bits/stdc++.h>

int V, E;
vector<int> adj[100001];

vector<pair<int, int>> artis;

int dfn[100001], max_dfn;
int bicon(int v, int u)
{
	bool arti = false;
	int low = (dfn[v] = ++max_dfn), low_w;
	for (int w : adj[v]) {
		if (w == u) {
			continue;
		}
		if (!dfn[w]) {
			low_w = bicon(w, v);
			if (dfn[v] < low_w) {	// articulation line detection (not equal)
				int a = v, b = w;
				if (!(a < b)) {
					swap(a, b);
				}
				artis.push_back({ a, b });
			}
		}
		else {
			low_w = dfn[w];
		}
		low = min(low, low_w);
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
	for (auto [v, w] : artis) {
		printf("%d %d\n", v, w);
	}
}
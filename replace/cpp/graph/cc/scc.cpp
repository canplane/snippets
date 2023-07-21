// BOJ 2150
// Tarjan's algorithm

using namespace std;
#include <bits/stdc++.h>

int V;
vector<int> adj[10001];

deque<int> st;
vector<vector<int>> sccs;
bool is_scc[10001];

int dfn[10001], max_dfn;
int tarjan(int v)
{
	int low = (dfn[v] = ++max_dfn);
	st.push_back(v);
	for (int w: adj[v]) {
		if (!dfn[w])
			low = min(low, tarjan(w));
		else if (!is_scc[w])
			low = min(low, dfn[w]);
	}
	if (low == dfn[v]) {
		sccs.push_back({}); auto &scc = sccs.back(); 
		while (true) {
			int w = st.back(); st.pop_back();
			is_scc[w] = true;
			scc.push_back(w);
			if (w == v)
				break;
		}
		sort(scc.begin(), scc.end());
	}
	return low;
}

int main()
{
	int E;
	scanf("%d %d", &V, &E);
	while (E--) {
		int a, b;
		scanf("%d %d", &a, &b);
		adj[a].push_back(b);
	}
	
	for (int v = 1; v <= V; v++)
		if (!dfn[v])
			tarjan(v);
	sort(sccs.begin(), sccs.end());

	printf("%ld\n", sccs.size());
	for (auto scc : sccs) {
		for (auto v : scc)
			printf("%d ", v);
		printf("-1\n");
	}
}
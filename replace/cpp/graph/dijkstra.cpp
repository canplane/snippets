// BOJ 1916

using namespace std;
#include <bits/stdc++.h>

#define INF ((1L << 31) - 1)

int N;
vector<pair<int, int>> adj[1001];

long dist[1001];
void dijkstra(int start)
{
	// init dist
	for (int i = 0; i < 1001; i++) {
		dist[i] = INF;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
	pq.push({ dist[start] = 0, start });
	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if (dist[u] < d) {
			continue;
		}
		for (auto [v, w] : adj[u]) {
			if (d + w < dist[v]) {
				pq.push({ dist[v] = d + w, v });
			}
		}
	}
}

// baseline
bool vis[1001];
void dijkstra_baseline(int u)
{
	for (int i = 0; i < 1001; i++) {
		dist[i] = INF;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

	pq.push({ dist[u] = 0, u });
	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if (vis[u]) {
			continue;
		}
		vis[u] = true;

		for (auto [v, w] : adj[u]) {
			if (!vis[v] && d + w < dist[v]) {
				pq.push({ dist[v] = d + w, v });
			}
		}
	}
}

int main()
{
	int M;
	scanf("%d %d", &N, &M);
	while (M--) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		adj[u].push_back({ v, w });
	}

	int A, B;
	scanf("%d %d", &A, &B);
	dijkstra(A);
	printf("%d", dist[B]);
}
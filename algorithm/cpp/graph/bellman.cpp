using namespace std;
#include <bits/stdc++.h>

#define INF ((1L << 30) - 1)

int N;
vector<pair<int, int>> adj[501];

long dist[501];
bool bellman(int start)
{
	// init dist
	for (int v = 1; v <= N; v++) {
		dist[v] = INF;
	}
	dist[start] = 0;

	for (int k = 0; k < N - 1; k++) {
		for (int u = 1; u <= N; u++) {
			for (auto [v, cost] : adj[u]) {
				dist[v] = min(dist[v], dist[u] + cost);
			}
		}
	}

	// negative cycle detection (if not exist, dist is valid)
	for (int u = 1; u <= N; u++) {
		for (auto [v, cost] : adj[u]) {
			if (dist[u] + cost < dist[v]) {
				return false;
			}
		}
	}
	return true;
}
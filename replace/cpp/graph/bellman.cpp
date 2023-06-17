using namespace std;
#include <cstdio>
#include <vector>
#include <utility>

int N, M;
vector<pair<int, int>> adj[501];

#define INF 0x7fffffff
long dist[501];
bool bellman(int v)
{
	for (int w = 1; w <= N; w++)
		dist[w] = INF;
	dist[v] = 0;

	for (int k = 0; k < N - 1; k++) {
		for (int v = 1; v <= N; v++) {
			for (auto [w, c] : adj[v]) {
				if (dist[v] != INF && dist[v] + c < dist[w]) {
					dist[w] = dist[v] + c;
				}
			}
		}
	}
	// negative cycle detection
	for (int v = 1; v <= N; v++) {
		for (auto [w, c] : adj[v]) {
			if (dist[v] != INF && dist[v] + c < dist[w]) {
				return false;
			}
		}
	}
	return true;
}
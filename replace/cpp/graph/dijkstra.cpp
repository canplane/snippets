// BOJ 1916

using namespace std;
#include <cstdio>
#include <vector>
#include <queue>
#include <utility>

int N;
vector<pair<int, int>> adj[1001];

#define INF 0x7fffffff
int dist[1001];
void dijkstra(int u)
{
	for (int i = 0; i < 1001; i++) {
		dist[i] = INF;
	}

	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

	pq.push({ dist[u] = 0, u });
	while (!pq.empty()) {
		auto [d, u] = pq.top(); pq.pop();
		if (dist[u] < d) {
			continue;
		}
		for (auto [v, w] : adj[u]) {
			if (dist[u] + w < dist[v]) {
				pq.push({ dist[v] = dist[u] + w, v });
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
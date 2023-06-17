using namespace std;
#include <cstdio>
#include <queue>
#include <tuple>

int N, M;
int A[100][100];

#define INF 0x7fffffff
int dist[100][100];
int dy[] = { -1, 0, 0, 1 };
int dx[] = { 0, -1, 1, 0 };
void dijkstra(int vy, int vx)
{
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < M; x++)
			dist[y][x] = INF;
	}

	priority_queue<tuple<int, int, int>> pq;
	dist[0][0] = 0, pq.push({ -dist[0][0], vy, vx });
	while (!pq.empty()) {
		auto [d, y, x] = pq.top(); pq.pop();
		d = -d;
		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i], nx = x + dx[i];
			if (!(0 <= ny && ny < N && 0 <= nx && nx < M))
				continue;
			if (dist[y][x] + A[ny][nx] < dist[ny][nx]) {
				dist[ny][nx] = dist[y][x] + A[ny][nx];
				pq.push({ -dist[ny][nx], ny, nx });
			}
		}
	}
}

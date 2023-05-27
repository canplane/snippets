using namespace std;
#include <cstdio>
#include <vector>
#include <deque>
#include <utility>

#define MAX_NODES 10
vector<int> adj[MAX_NODES];

bool visit[MAX_NODES];

void dfs(int v)
{
	visit[v] = true;
	// PRE
	printf("%d ", v);
	for (auto w : adj[v]) {
		if (!visit[w]) {
			dfs(w);
			// IN
		}
	}
	// POST
}
void dfs_iter(int v)
{
	deque<pair<int, bool>> s;
	s.push_back({ v, false });
	while (s.size()) {
		auto [v, post] = s.back(); s.pop_back();
		if (!visit[v]) {
			visit[v] = true;
			// PRE
			printf("%d ", v);
			s.push_back({ v, true });	// push same node again for postorder
			for (auto w = adj[v].rbegin(); w != adj[v].rend(); w++) {	// reversed iterator
				s.push_back({ *w, false });
			}
		}
		else if (post) {
			// POST (+ IN if the child has the context for parent)
		}
	}
}

void bfs(int v)
{
	deque<int> q;
	visit[v] = true, q.push_back(v);
	while (q.size()) {
		v = q.front(), q.pop_front();
		// PRE
		printf("%d ", v);
		for (auto w : adj[v]) {
			if (!visit[w])
				visit[w] = true, q.push_back(w);
		}
	}
}
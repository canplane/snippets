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
/* // simulates computer architecture
void dfs_iter2(int v)
{
	deque<int> s;
	bool call;
	int ret, i;

	visit[v] = true;
	{ ( s.push_back(v), s.push_back(0) ); s.push_back(0); call = true; }		// callee context
	// v, i, ret -> ret
	while (true) {
		{ call = false; (ret = s.back(), s.pop_back()); ( (i = s.back(), s.pop_back()), (v = s.back(), s.pop_back()) ); }

		if (i == 0) {
			printf("%d ", v);
			ret++;
		}
		for (; i < adj[v].size(); i++) {
			int w = adj[v][i];
			if (!visit[w]) {
				visit[w] = true;
				{ ( s.push_back(v), s.push_back(i + 1) ); }									// caller context
				{ ( s.push_back(w), s.push_back(0) ); s.push_back(ret); call = true; }		// callee context
				break;
			}
		}
		if (call)	continue;
		{ s.push_back(ret); if (s.size() == 1) break; }
	}
	{ call = false; (ret = s.back(), s.pop_back()); }
}
 */
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
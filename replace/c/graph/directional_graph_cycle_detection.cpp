using namespace std;
#include <cstdio>
#include <vector>
#include <algorithm>
#include <deque>

#define INF (1 << 30)

// data: https://victorydntmd.tistory.com/97
#define N 7
vector<int> adj[1 + N] = {
	{},
	{ 2, 5 },
	{ 3 },
	{ 1, 4 },
	{},
	{ 4 },
	{ 5, 7 },
	{ 5 },
};
int dep[1 + N], cycle_dep;
bool finish[1 + N];

int cycle_nodes;

deque<int> s;
bool dfs(int v, int d)
{
	dep[v] = d;
	
	bool is_cycle = false;
	s.push_back(v);
	for (int w : adj[v]) {
		if (!dep[w]) {
			is_cycle |= dfs(w, d + 1);
		}
		else if (!finish[w] && dep[w] <= dep[v]) {
			is_cycle = true;
			cycle_dep = min(cycle_dep, dep[w]);

			printf("size %d cycle detection: ", dep[v] - dep[w] + 1);
			for (auto it = s.rbegin(); *it != w; it++)	printf("%d <- ", *it);
			printf("%d\n", w);
		}
	}
	if (is_cycle) {
		cycle_nodes++;
		if (d == cycle_dep)	is_cycle = false, cycle_dep = INF;
	}
	s.pop_back();

	finish[v] = true;
	return is_cycle;
}

int main()
{
	for (int v = 1; v <= N; v++) {
		if (!dep[v]) {
			cycle_dep = INF;
			dfs(v, 1);
		}
	}
	printf("total cycle nodes: %d\n", cycle_nodes);
}
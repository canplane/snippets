// 사이클 개수 세기
// 유방향이든 무방향이든 그래프의 사이클 개수를 구하는 것은 NP-hard. (TSP 생각)
// 그러나 BOJ 16724(피리 부는 사나이)와 같이 out-degree가 1로 고정된다면 back edge의 수가 사이클 개수가 됨.
// 이 코드는 사이클 유무는 보장하나, 어느 경로인지, 그리고 사이클이 몇 개인지는 탐지해줄 수 없음. (즉, 경로 출력을 위해 스택 등 짜둔 건 오류)

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
		else if (!finish[w]) {
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
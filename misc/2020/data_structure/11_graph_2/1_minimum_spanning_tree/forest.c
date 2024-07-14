/* disjoint set을 cycle 판별 이외에도 MST 구조로 이용할 수 있도록 수정 (forest_union(), forest_setRoot())
 * 20200205
 */

void forest_init(int parent[], int size)
{
    while (--size + 1)
        parent[size] = -1;
}

int forest_find(int parent[], int x)
{
    for (; parent[x] >= 0; x = parent[x]);
    return x;
}

// x가 루트 노드가 되도록 트리를 수정
void forest_setRoot(int parent[], int x)
{
    int lead, trail, tmp;
    if (parent[x] >= 0) {
        for (lead = parent[trail = x]; parent[lead] >= 0; trail = lead, lead = tmp) {
            tmp = parent[lead];
            parent[lead] = trail;
        }
        parent[x] = parent[lead];
        parent[lead] = trail;
    }
}

// x의 트리에 y의 트리를 추가 (한 쪽의 루트는 유지)
void forest_union(int parent[], int x, int y)
{
    int root, tmp;
    root = forest_find(parent, x);
    forest_setRoot(parent, y);
    tmp = parent[y];
    parent[y] = x;
    parent[root] += tmp;
}

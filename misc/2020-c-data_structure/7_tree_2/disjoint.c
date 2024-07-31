/* disjoint set (set representation)
 * 20200203
 * 데이터 수 많으면 find -> collapsingFind, simpleUnion -> weightedUnion 이용
 * e.g. equivalent class(symbol : three =), cycle
 * weightedUnion(x, y)은 둘 다 루트 값이 같다면 x 쪽을 루트로 유지하도록 하자 
 */

#define MAXSZ 10

int _parent[MAXSZ];

void init(int size)
{
    while (--size + 1)
        _parent[size] = -1;
}

int find(int x)
{
    for (; _parent[x] >= 0; x = _parent[x]);
    return x;
}

int collapsingFind(int x)
{
    int root, tmp;
    for (root = x; _parent[root] >= 0; root = _parent[root]);
    for (; x != root; x = tmp) {
        tmp = _parent[x];
        _parent[x] = root;
    }
    return root;
}

void simpleUnion(int x, int y)
{
    x = find(x), y = find(y);
    if (x != y) //
        _parent[x] = y;
}

void weightedUnion(int x, int y)
{
    int tmp;
    x = find(x), y = find(y);
    if (x != y) {   //
        tmp = _parent[x] + _parent[y];
        if (_parent[x] <= _parent[y]) { // 둘이 같으면 좌항에 붙도록
            _parent[y] = x;
            _parent[x] = tmp;
        }
        else {
            _parent[x] = y;
            _parent[y] = tmp;
        }
    }
}

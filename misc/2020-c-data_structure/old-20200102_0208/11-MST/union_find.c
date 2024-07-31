#define MAXSZ 100

static int _parent[MAXSZ];

void _make_set(int n)
{
    for (int i = 0; i < n; i++)
        _parent[i] = i;
}

int _find(int x)
{
    if (_parent[x] == x)
        return x;
    return _find(_parent[x]);        
}

void _union(int x, int y)
{
    x = _find(x);
    y = _find(y);
    _parent[y] = x;
}
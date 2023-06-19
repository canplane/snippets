using namespace std;
#include <utility>

// 좌표 압축: { 1, 1, 10, 5, 3 } -> { 0, 1, 4, 3, 2 }
// 최댓값은 (배열 사이즈 - 1) 보장
template <class T>
void compress_coord(T arr[], int n)
{
	pair<T, int> p[n];
	for (int i = 0; i < n; i++) {
		p[i] = { arr[i], i };
	}
	sort(p, p + n);
	int j = 0;
	for (int i = 0; i < n; i++) {
		j += (i > 0 && p[i].first != p[i - 1].first);
		arr[p[i].second] = j;
	}
}
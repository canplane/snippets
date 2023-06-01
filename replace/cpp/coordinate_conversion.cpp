// 좌표 압축: { 1, 1, 10, 5, 3 } -> { 0, 1, 4, 3, 2 }
// 최댓값은 (배열 사이즈 - 1) 보장
template <class T>
void convert_coord(T arr[], int n)
{
	vector<pair<T, int>> v(n);
	for (int i = 0; i < n; i++) {
		v[i] = { arr[i], i };
	}
	sort(v.begin(), v.end());
	for (int i = 0; i < n; i++) {
		arr[v[i].second] = i;
	}
}
'''
x in [lower_bound, upper_bound)
bisect_left == lower_bound
bisect_right == upper_bound
'''

# naive: bisect가 더 빠름
# [l, r)
def find(arr, l, r, k):
	while l < r:
		m = (l + r) // 2
		if k == arr[m]:
			return k
		elif k < arr[m]:
			r = m
		else:
			l = m + 1
	return -1
def lower_bound(arr, l, r, k):
	while l < r:
		m = (l + r) // 2
		if k <= arr[m]:
			r = m
		else:
			l = m + 1
	return l
def upper_bound(arr, l, r, k):
	while l < r:
		m = (l + r) // 2
		if k < arr[m]:
			r = m
		else:
			l = m + 1
	return l


# example

bs = [1, 2, 2, 2, 4, 4, 4, 5, 6]

print(lower_bound(bs, 0, len(bs), 2), upper_bound(bs, 0, len(bs), 2))
print(lower_bound(bs, 0, len(bs), 3), upper_bound(bs, 0, len(bs), 3))

from bisect import bisect_left, bisect_right
print(bisect_left(bs, 2), bisect_right(bs, 2))
print(bisect_left(bs, 3), bisect_right(bs, 3))
# default: lo=0, hi=len(bs)
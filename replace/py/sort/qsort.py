from random import random

N, k = map(int, input().split())
A = list(map(int, input().split()))

def sort(l, r):
	global A
	if l == r:	return

	piv = A[l + int((r - l) * random())]
	i, j = l - 1, r
	while True:
		while A[i := i + 1] < piv:  pass
		while A[j := j - 1] > piv:  pass
		if i >= j:	break
		A[i], A[j] = A[j], A[i]
	
	sort(l, i); sort(j + 1, r)

def nth_element(l, r, k):
	global A

	piv = A[l + int((r - l) * random())]
	i, j = l - 1, r
	while True:
		while A[i := i + 1] < piv:  pass
		while A[j := j - 1] > piv:  pass
		if i >= j:	break
		A[i], A[j] = A[j], A[i]
	
	if i == j == k:
		return A[k]
	if k < i:
		return nth_element(l, i, k)
	else:
		return nth_element(j + 1, r, k)
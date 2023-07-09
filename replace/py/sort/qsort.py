from random import random

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

def nth_element(l, r, nth):
	global A
	if l == r: return

	piv = A[l + int((r - l) * random())]
	i, j = l - 1, r
	while True:
		while A[i := i + 1] < piv:  pass
		while A[j := j - 1] > piv:  pass
		if i >= j:	break
		A[i], A[j] = A[j], A[i]
	
	if nth < i:
		nth_element(l, i, nth)
	else:
		nth_element(j + 1, r, nth)
	
# variation: returns the n-th value directly
def nth_element2(l, r, nth):
	global A

	piv = A[l + int((r - l) * random())]
	i, j = l - 1, r
	while True:
		while A[i := i + 1] < piv:  pass
		while A[j := j - 1] > piv:  pass
		if i >= j:	break
		A[i], A[j] = A[j], A[i]
	
	if i == j == nth:
		return A[nth]
	if nth < i:
		return nth_element2(l, i, nth)
	else:
		return nth_element2(j + 1, r, nth)


N, k = map(int, input().split())
A = list(map(int, input().split()))
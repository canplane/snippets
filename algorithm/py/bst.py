def find_and_insert(root, k):
	parent = None; node = root
	while node:
		if node[0] == k:
			break
		parent = node; node = parent[1 if parent[0] < k else 2]
	if not node:
		node = [k, None, None]
		if parent:
			parent[1 if parent[0] < k else 2] = node
		else:
			root = node
	return node
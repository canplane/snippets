# floor(x/y), ceil(x/y)
def _floor(x: int, y: int):
	return x // y
def _ceil(x: int, y: int):
	return x // y + (x % y != 0)
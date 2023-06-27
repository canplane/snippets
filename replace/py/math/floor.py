# * C나 Python이나 int()는 truncate: int(3.2) = 3, int(-3.2) = -3
#
# * 나눗셈:
#	C는 버림처럼 동작 (나머지는 음수 가능),
#	Python은 내림처럼 동작 (나머지는 음수 아님)
#
# * 라운딩:
# 	Python은 math.round 오류! (round half to even)
# 	printf 포맷팅 역시 라운딩 오류가 있으니 쓰지 말자
#	이게 제일 좋음: floor(x + 0.5)

def _floor(x: float):	# OR int(x // 1) if Python (not C!)
	_x = int(x)
	if x == _x:	return _x
	return _x - (x < 0)
def _ceil(x: float):
	_x = _floor(x)
	return _x + (x != _x)
def _round(x: float):
	return _floor(x + 0.5)


# debug :
def debug():
	li = [0, 2, 2.25, 2.5, -2, -2.25, -2.5]
	print(*li)
	print("floor", *map(_floor, li))
	print("ceil", *map(_ceil, li))
	print("round", *map(_round, li))
debug()


# floor(x/y), ceil(x/y): if C, only safe on positive numbers
def _floor_div(x: int, y: int):
	return x // y
def _ceil_div(x: int, y: int):
	return x // y + (x % y != 0)
# 2 <= b <= 36
i = 16; s = "16"; b = 10


# atoi: In C, strtol(s, &end_ptr, b) (atoi(s) == strtol(s, NULL, 10))
# long int는 64비트 시스템에서 기본적으로 8바이트. 윈도에서만 4바이트!
int(s, base=b)


# itoa: In C, sprintf()
bin(i); oct(i); str(i); hex(i)

ALPHA = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
def to_string(n, base=10):
	ret = []
	while n > 0:
		n, r = n // base, n % base
		ret.append(ALPHA[r])
	return "".join(ret[::-1])
to_string(i, base=b)
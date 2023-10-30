#define			SWAP(x, y, t)		((t) = (x), (x) = (y), (y) = (t))
/* 임시 변수 없는 swap. 같은 값이라도 오류가 일어나지 않음. 비트 연산이므로 정수형에서만 적용 가능 */
#define			SWAP(x, y)			(((x) != (y)) && ((y) ^= (x), (x) ^= (y), (y) ^= (x)))


#define			MIN2(x, y)			((x) > (y) ? (y) : (x))
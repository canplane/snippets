/* malloc 간이 구현. 오버헤드 줄일 수 있음. free()는 없음 */
#define			malloc(size)							_malloc(size)
char loc[1000000], *p = loc;
void *_malloc(int size)
{
	char *tmp;
	tmp = p, p += size;
	return tmp;
}
/* memset 구현. void * 사용하려면 int *나 char *로 캐스팅 필요. (error: operand of type 'void' where arithmetic or pointer type is required)
void *의 ++은 char *와 같음 (1 증가) */
#define			memset(p, c, len)						_memset(p, c, len)
void _memset(void *p, char c, int len)
{
	while (len--)
		*((char *)p++) = c;
}


int _strcmp(char *p, char *q)
{
	int ret;
	while (!(ret = *p - *q) && *p)
		p++, q++;
	return ret;
}


void _strcpy(char *dst, char *src)
{
	while (*dst++ = *src++);
}


int _strlen(char *s)
{
	int i;
	i = 0;
	while (*s++)
		i++;
	return i;
}
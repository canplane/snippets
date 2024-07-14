#include <time.h>
#include <stdio.h>
#define BUFSIZE	128

int main(void)
{
	time_t cal;
	struct tm *tmptr;
	char buf[BUFSIZE];

	time(&cal);
	tmptr = localtime((const time_t *)&cal);
	/* if you use gmtime instead localtime, strftime will convert the structure to a string in UTC */ 
	strftime(buf, BUFSIZE, "%a %b %d %H:%M:%S %Z %Y", tmptr); 
	printf("%s\n", buf);
	return 0;
}

#include <sys/utsname.h>
#include <stdio.h>
#define	SYS	01
#define NOD	02
#define RLS	04
#define VER	010
#define MAC	020

int option(char *);

int main(int argc, char *argv[])	{
	struct utsname utbuf;
	int flag;
	
	if (uname(&utbuf) == -1)	return -1;

	if (argc > 1) {
		if ((flag = option(argv[1])) == EOF)	return -1;
	}
	else	flag = SYS;
	
	printf("%s %s %s %s %s\n", 
		(flag & SYS)?	utbuf.sysname:	"",
		(flag & NOD)?	utbuf.nodename:	"",
		(flag & RLS)?	utbuf.release:	"",
		(flag & VER)?	utbuf.version:	"",
		(flag & MAC)?	utbuf.machine:	""
	);

	return 0;
}

int option(char *arg)	{
	int temp = 0;

	if (*arg++ != '-')	return EOF;

	while (*arg)
		switch(*arg++)	{
		case 's':
			if ((temp ^= SYS) & SYS)	break;
			return EOF;
		case 'n':
			if ((temp ^= NOD) & NOD)	break;
			return EOF;
		case 'r':
			if ((temp ^= RLS) & RLS)	break;
			return EOF;
		case 'v':
			if ((temp ^= VER) & VER)	break;
			return EOF;
		case 'm':
			if ((temp ^= MAC) & MAC)	break;
			return EOF;
		default:
			return EOF;
		}

	return temp;
}

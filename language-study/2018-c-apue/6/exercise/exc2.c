/* Superuser permission is necessary! */

#include <shadow.h>
#include <pwd.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct spwd	*spbuf;
	setspent();
	while ((spbuf = getspent()) != NULL)
		if (!strcmp(spbuf->sp_namp, \
		((argc > 1)? argv[1]: getpwuid(getuid())->pw_name)))
			break;
	if (errno) {
		perror(NULL);
		return 1;
	}
	printf("%s\n", spbuf->sp_pwdp);
	return 0;
}

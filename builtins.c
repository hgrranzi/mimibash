#include "mimibash.h"

int	exec_pwd(int fd)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
		return (cmd_error("pwd", errno));
	write(fd, wd, strlen(wd));
	write(fd, "\n", 1);
	free(wd);
	wd = NULL;
	return (0);
}

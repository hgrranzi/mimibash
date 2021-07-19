#include "mimibash.h"

int	exec_echo(int fd, char **arg)
{
	if (arg)
		write(fd, *arg, strlen(*arg));
	else
		write(fd, "\n", 1);
	return (0);
}

int	exec_cd(int fd, char **arg)
{
	return (0);
}

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

int	exec_export(int fd, char **arg)
{
	return (0);
}

int	exec_unset(int fd, char **arg)
{
	return (0);
}

int	exec_env(int fd, char **arg)
{
	return (0);
}

int	exec_exit(int fd, char **arg)
{
	int	return_code;

	return_code = 0;//need to take the last return code
	write(fd, "\b\b", 2); // temporary
	write(fd, "exit\n", 6); // temporary
	if (arg)
		return_code = atoi(*arg); // need an arg checker for errors
	exit(return_code);
}

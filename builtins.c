#include "mimibash.h"

int	exec_echo(int *fd, char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		if (i)
			write(fd[OUT], " ", 1);
		write(fd[OUT], arg[i], strlen(arg[i]));
		i++;
	}
	return (0);
}

int	exec_cd(int *fd, char **arg)
{
	return (0);
}

int	exec_pwd(int *fd, char **arg)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
		error_and_exit("pwd", NULL, 0);
	write(fd[OUT], wd, strlen(wd));
	write(fd[OUT], "\n", 1);
	free(wd);
	wd = NULL;
	return (0);
}

int	exec_export(int *fd, char **arg)
{
	return (0);
}

int	exec_unset(int *fd, char **arg)
{
	return (0);
}

int	exec_env(int *fd, char **arg)
{
	return (0);
}

int	exec_exit(int *fd, char **arg)
{
	int	exit_code;

	exit_code = 0;//need to take the last return code
	write(fd[OUT], "\b\b", 2); // temporary
	write(fd[OUT], "exit\n", 6); // temporary
	if (arg)
	{
		if (only_digits(*arg))
			exit_code = atoi(*arg); // need an arg checker for errors
		else
			exit_code = 255;
	}
	exit((exit_code + 256) % 256);
}

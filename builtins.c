#include "mimibash.h"

int	exec_echo(int *fd, char **arg, char **envp)
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

int	exec_cd(int *fd, char **arg, char **envp)
{
	char	*new_wd;
	int		i;

	i = 0;
	if (chdir(arg[1]) == 0)
	{
		new_wd = getcwd(NULL, 0);
		if (new_wd)
		{
			while (envp[i])
			{
				if (strncmp(envp[i], "PWD=", 4) == 0)
				{
					free(envp[i]);
					envp[i] = aka_strjoin("PWD=", new_wd);
					if (!envp[i])
						error_and_exit(NULL, NULL, 1);
					break ;
				}
				i++;
			}
		}
		else
			error_and_exit("cd", NULL, 0);
	}
	else
		error_and_exit("cd", NULL, 0);
	printf("%s\n", envp[i]);
	printf("%s\n", new_wd);
	return (0);
}

int	exec_pwd(int *fd, char **arg, char **envp)
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

int	exec_export(int *fd, char **arg, char **envp)
{
	return (0);
}

int	exec_unset(int *fd, char **arg, char **envp)
{
	return (0);
}

int	exec_env(int *fd, char **arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		write(fd[OUT], envp[i], strlen(envp[i]));
		write(fd[OUT], "\n", 1);
		i++;
	}
	return (0);
}

int	exec_exit(int *fd, char **arg, char **envp)
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

#include "mimibash.h"

int	exec_echo(int *fd, char **arg, char **envp)
{
	int	i;

	i = 0;
	while (arg && arg[i])
	{
		write(fd[OUT], arg[i], strlen(arg[i]));
		if (i && arg[i + 1] && arg[i + 1][0] != '\n')
			write(fd[OUT], " ", 1);
		i++;
	}
	return (0);
}

int	exec_cd(int *fd, char **arg, char **envp)
{
	char	*new_wd;
	int		i;

	i = 0;
	if (!arg[1] || chdir(arg[1]) == 0)
	{
		new_wd = getcwd(NULL, 0);
		while (new_wd && envp[i])
		{
			if (strncmp(envp[i], "PWD=", 4) == 0)
			{
				free(envp[i]);
				envp[i] = aka_strjoin("PWD=", new_wd);
				if (!envp[i])
					error_and_exit(NULL, NULL, 1);
				free(new_wd);
				return (0);
			}
			i++;
		}
	}
	else
		error_and_exit("cd", NULL, 0);
	return (1);
}

int	exec_pwd(int *fd, char **arg, char **envp)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
	{
		error_and_exit("pwd", NULL, 0);
		return (1);
	}
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

void	remove_variable(char *arg, char **envp)
{
	int	i;
	int	arg_len;

	i = 0;
	arg_len = strlen(arg);
	while (envp[i])
	{
		if (strncmp(envp[i], arg, arg_len) == 0 && envp[i][arg_len] == '=')
		{
			free(envp[i]);
			envp[i] = strdup("\0");
			if (!envp[i])
				error_and_exit(NULL, NULL, 1);
			break ;
		}
		i++;
	}
}

int	exec_unset(int *fd, char **arg, char **envp)
{
	int	i;
	int	exit_code;

	i = 1;
	exit_code = 0;
	while (arg[i])
	{
		if (!arg[i][0])
			exit_code = 1;
		else
			remove_variable(arg[i], envp);
		i++;
	}
	return (exit_code);
}

int	exec_env(int *fd, char **arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0])
		{
			write(fd[OUT], envp[i], strlen(envp[i]));
			write(fd[OUT], "\n", 1);
		}
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

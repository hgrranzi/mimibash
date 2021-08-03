#include "mimibash.h"

int	exec_echo(int *fd, char **arg, char ***envp)
{
	char	***no_need;
	int		i;

	no_need = envp;
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

char	*take_var(char **envp, char *var)
{
	char	*home;
	int		i;

	home = NULL;
	i = 0;
	while (envp[i])
	{
		if (strncmp(var, envp[i], strlen(var)) == 0 && envp[i][strlen(var)] == '=')
		{
			home = strdup(&(envp[i][5]));
			if (!home)
				error_and_exit(NULL, NULL, 1);
			return (home);
		}
		i++;
	}
	return (home);
}

void	update_wd_var(char ***envp, char *new_wd, int i)
{
	char	*old_wd;
	char	*oldpwd;

	old_wd = strdup(&(*envp)[i][4]);
	if (!old_wd)
		error_and_exit(NULL, NULL, 1);
	oldpwd = aka_strjoin("OLDPWD=", old_wd);
	if (!oldpwd)
		error_and_exit(NULL, NULL, 1);
	free(old_wd);
	find_variable("OLDPWD", 6, oldpwd, *envp) || find_place(oldpwd, *envp) || new_place(oldpwd, envp);
	free(oldpwd);
	free((*envp)[i]);
	(*envp)[i] = aka_strjoin("PWD=", new_wd);
	if (!(*envp)[i])
		error_and_exit(NULL, NULL, 1);
	free(new_wd);
}

int	exec_cd(int *fd, char **arg, char ***envp)
{
	int		*no_need;
	char	*new_wd;
	int		i;

	no_need = fd;
	i = 0;
	//error_and_exit("cd", ERR_HOME, 0);
	if (!arg[1] || chdir(arg[1]) == 0)
	{
		new_wd = getcwd(NULL, 0);
		while (new_wd && (*envp)[i])
		{
			if (strncmp((*envp)[i], "PWD=", 4) == 0)
			{
				update_wd_var(envp, new_wd, i);
				return (0);
			}
			i++;
		}
		remove_variable("OLDPWD", *envp);
	}
	else
		error_and_exit("cd", NULL, 0);
	return (1);
}

int	exec_pwd(int *fd, char **arg, char ***envp)
{
	char	**no_need;
	char	***no_need2;
	char	*wd;

	no_need = arg;
	no_need2 = envp;
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

int	exec_export(int *fd, char **arg, char ***envp)
{
	int		i;
	int		var_len;
	char	*var;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (!arg[i])
		return (print_sorted_env(fd, *envp));
	while (arg[i])
	{
		if (!arg[i][0])
			exit_code = 1;
		else if (strchr(arg[i], '='))
		{
			var_len = index_char(arg[i], '=');
			var = strndup(arg[i], var_len);
			if (!var)
				error_and_exit(NULL, NULL, 1);
			find_variable(var, var_len, arg[i], *envp) || find_place(arg[i], *envp) || new_place(arg[i], envp);
			free(var);
		}
		i++;
	}
	return (exit_code);
}

int	exec_unset(int *fd, char **arg, char ***envp)
{
	int	*no_need;
	int	i;
	int	exit_code;

	no_need = fd;
	i = 1;
	exit_code = 0;
	while (arg[i])
	{
		if (!arg[i][0])
			exit_code = 1;
		else
			remove_variable(arg[i], *envp);
		i++;
	}
	return (exit_code);
}

int	exec_env(int *fd, char **arg, char ***envp)
{
	char	**no_need;
	int		i;

	no_need = arg;
	i = 0;
	while ((*envp)[i])
	{
		if ((*envp)[i][0])
		{
			write(fd[OUT], (*envp)[i], strlen((*envp)[i]));
			write(fd[OUT], "\n", 1);
		}
		i++;
	}
	return (0);
}

int	exec_exit(int *fd, char **arg, char ***envp)
{
	char	***no_need;
	int		exit_code;

	no_need = envp;
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

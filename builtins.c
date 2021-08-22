#include "mimibash.h"

int	exec_echo(int *fd, char **arg, char ***envp)
{
	char	***no_need;
	int		i;

	no_need = envp;
	i = 1;
	while (arg && arg[i])
	{
		write(fd[OUT], arg[i], ft_strlen(arg[i]));
		if (i && arg[i + 1] && arg[i + 1][0] != '\n')
			write(fd[OUT], " ", 1);
		i++;
	}
	if (fd[IN] != IN)
		close(fd[IN]);
	if (fd[OUT] != OUT)
		close(fd[OUT]);
	return (0);
}

char	*take_var(char **envp, char *var)
{
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while (envp[i])
	{
		if (strncmp(var, envp[i], ft_strlen(var)) == 0 && envp[i][strlen(var)] == '=')
		{
			value = ft_strdup(&(envp[i][strlen(var) + 1]));
			if (!value)
				error_and_exit(NULL, NULL, 1);
			return (value);
		}
		i++;
	}
	return (value);
}

int	update_wd_var(char ***envp, char *new_wd, int i)
{
	char	*old_wd;
	char	*oldpwd;

	old_wd = ft_strdup(&(*envp)[i][4]);
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
	return (0);
}

char	*check_dir(char *arg, char **envp)
{
	char	*go_to;

	if (!arg)
	{
		go_to = take_var(envp, "HOME");
		if (!go_to)
			error_and_exit("cd", ERR_HOME, 0);
	}
	else
	{
		go_to = ft_strdup(arg);
		if (!go_to)
			error_and_exit(NULL, NULL, 1);
	}
	return (go_to);
}

int	exec_cd(int *fd, char **arg, char ***envp)
{
	int		*no_need;
	char	*new_wd;
	char	*go_to;
	int		i;

	no_need = fd;
	i = 0;
	go_to = check_dir(arg[1], *envp);
	if (!go_to || (arg[1] && !arg[1][0]))
		return (1);
	if (chdir(go_to) == 0)
	{
		free(go_to);
		new_wd = getcwd(NULL, 0);
		while (new_wd && (*envp)[i])
		{
			if (strncmp((*envp)[i], "PWD=", 4) == 0)
				return (update_wd_var(envp, new_wd, i));
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
	write(fd[OUT], wd, ft_strlen(wd));
	write(fd[OUT], "\n", 1);
	free(wd);
	wd = NULL;
	if (fd[IN] != IN)
		close(fd[IN]);
	if (fd[OUT] != OUT)
		close(fd[OUT]);
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
			write(fd[OUT], (*envp)[i], ft_strlen((*envp)[i]));
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
	exit_code = 0;
	if (fd[IN] == STDIN_FILENO)
		write(STDERR_FILENO, "exit\n", 6);
	if (only_digits(arg[1]))
		exit_code = ft_atoi(arg[1]);
	else
	{
		error_and_exit("exit", ERR_EXIT, 0);
		exit_code = 255;
	}
	close(fd[IN]);
	close(fd[OUT]);
	exit((exit_code + 256) % 256);
}

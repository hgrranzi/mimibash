#include "mimibash.h"

char	*take_var(char **envp, char *var)
{
	char	*value;
	int		i;

	value = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(var, envp[i], ft_strlen(var)) == 0 && envp[i][strlen(var)] == '=')
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
	char	*newwd;

	old_wd = ft_strdup(&(*envp)[i][4]);
	if (!old_wd)
		error_and_exit(NULL, NULL, 1);
	oldpwd = aka_strjoin("OLDPWD=", old_wd);
	newwd = aka_strjoin("PWD=", new_wd);
	if (!oldpwd || !newwd)
		error_and_exit(NULL, NULL, 1);
	free(old_wd);
	free(new_wd);
	find_variable("OLDPWD", 6, oldpwd, *envp) || find_place(oldpwd, *envp) || new_place(oldpwd, envp);
	free(oldpwd);
	find_variable("PWD", 3, newwd, *envp) || find_place(newwd, *envp) || new_place(newwd, envp);
	free(newwd);
	if (!(*envp)[i])
		error_and_exit(NULL, NULL, 1);
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
			if (ft_strncmp((*envp)[i], "PWD=", 4) == 0)
				return (update_wd_var(envp, new_wd, i));
			i++;
		}
		remove_variable("OLDPWD", *envp);
	}
	else
	{
		free(go_to);
		error_and_exit("cd", NULL, 0);
	}
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
	return (0);
}

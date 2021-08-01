#include "mimibash.h"

int	exec_echo(int *fd, char **arg, char ***envp)
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

int	exec_cd(int *fd, char **arg, char ***envp)
{
	char	*new_wd;
	int		i;

	i = 0;
	if (!arg[1] || chdir(arg[1]) == 0)
	{
		new_wd = getcwd(NULL, 0);
		while (new_wd && (*envp)[i])
		{
			if (strncmp((*envp)[i], "PWD=", 4) == 0)
			{
				free((*envp)[i]);
				(*envp)[i] = aka_strjoin("PWD=", new_wd);
				if (!(*envp)[i])
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

int	exec_pwd(int *fd, char **arg, char ***envp)
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

int	find_variable(char *var, int var_len, char *arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], arg, var_len) == 0 && envp[i][var_len] == '=')
		{
			free(envp[i]);
			envp[i] = strdup(arg);
			if (!envp[i])
				error_and_exit(NULL, NULL, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	find_place(char *arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!envp[i][0])
		{
			free(envp[i]);
			envp[i] = strdup(arg);
			if (!envp[i])
				error_and_exit(NULL, NULL, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	new_place(char *arg, char ***envp) // need to be fixed
{
	int		new_envp_size;
	char	**tmp_arr;
	int		i;

	tmp_arr = copy_arr(*envp);
	new_envp_size = count_arr_size(*envp) + 1;
	free_arr(*envp);
	*envp = malloc((new_envp_size + 1) * sizeof(char *));
	if (!*envp)
		error_and_exit(NULL, NULL, 1);
	(*envp)[0] = strdup(arg);
	if (!(*envp)[0])
		error_and_exit(NULL, NULL, 1);
	i = 1;
	while (tmp_arr[i - 1])
	{
		(*envp)[i] = strdup(tmp_arr[i - 1]);
		if (!(*envp)[i])
			error_and_exit(NULL, NULL, 1);
		i++;
	}
	(*envp)[new_envp_size] = NULL;
	free_arr(tmp_arr);
	tmp_arr = NULL;
	return (0);
}

char	*quote_str(char *str)
{
	char	*new_str;
	int		new_len;
	int		i;
	int		j;
	int		quote_index;

	new_len = strlen(str) + 2;
	new_str = malloc((new_len + 1) * sizeof(char));
	if (!new_str)
		error_and_exit(NULL, NULL, 1);
	new_str[new_len] = '\0';
	new_str[new_len - 1] = '\"';
	quote_index = index_char(str, '=') + 1;
	i = 0;
	j = 0;
	while (i < new_len - 1)
	{
		new_str[i] = str[j];
		if (i == quote_index)
		{
			new_str[i] = '\"';
			j--;
		}
		j++;
		i++;
	}
	return (new_str);
}

char	**add_quotes(char **arr)
{
	char	**quoted_arr;
	int		arr_len;
	int		i;

	arr_len = count_arr_size(arr);
	quoted_arr = malloc((arr_len + 1) * sizeof (char *));
	if (!quoted_arr)
		error_and_exit(NULL, NULL, 1);
	quoted_arr[arr_len] = NULL;
	i = 0;
	while (arr[i])
	{
		if (arr[i][0])
			quoted_arr[i] = quote_str(arr[i]);
		else
			quoted_arr[i] = strdup(arr[i]);
		i++;
	}
	return(quoted_arr);
}

int	print_sorted_env(int *fd, char **envp)
{
	int		i;
	char	**quoted_envp;

	//sort_env();
	quoted_envp = add_quotes(envp);
	i = 0;
	while (quoted_envp[i])
	{
		if (quoted_envp[i][0])
		{
			write(fd[OUT], ENV_PREFIX, strlen(ENV_PREFIX));
			write(fd[OUT], " ", 1);
			write(fd[OUT], quoted_envp[i], strlen(quoted_envp[i]));
			write(fd[OUT], "\n", 1);
		}
		i++;
	}

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

int	exec_unset(int *fd, char **arg, char ***envp)
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
			remove_variable(arg[i], *envp);
		i++;
	}
	return (exit_code);
}

int	exec_env(int *fd, char **arg, char ***envp)
{
	int	i;

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

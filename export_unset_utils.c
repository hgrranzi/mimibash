#include "mimibash.h"

int	find_variable(char *var, int var_len, char *arg, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, var_len) == 0 && envp[i][var_len] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup(arg);
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
			envp[i] = ft_strdup(arg);
			if (!envp[i])
				error_and_exit(NULL, NULL, 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	new_place(char *arg, char ***envp)
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
	(*envp)[0] = ft_strdup(arg);
	if (!(*envp)[0])
		error_and_exit(NULL, NULL, 1);
	i = 1;
	while (tmp_arr[i - 1])
	{
		(*envp)[i] = ft_strdup(tmp_arr[i - 1]);
		if (!(*envp)[i])
			error_and_exit(NULL, NULL, 1);
		i++;
	}
	(*envp)[new_envp_size] = NULL;
	free_arr(tmp_arr);
	tmp_arr = NULL;
	return (0);
}

void	remove_variable(char *arg, char **envp)
{
	int	i;
	int	arg_len;

	i = 0;
	arg_len = ft_strlen(arg);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], arg, arg_len) == 0 && envp[i][arg_len] == '=')
		{
			free(envp[i]);
			envp[i] = ft_strdup("\0");
			if (!envp[i])
				error_and_exit(NULL, NULL, 1);
			break ;
		}
		i++;
	}
}

int	exec_error(int *fd, char **arg, char ***envp)
{
	if (fd && arg && envp)
		;
	if (arg && ft_atoi(arg[0]) == 258)
		return (258);
	return (1);
}

#include "mimibash.h"

char	*quote_str(char *str)
{
	char	*new_str;
	int		new_len;
	int		i;
	int		j;
	int		quote_index;

	new_len = ft_strlen(str) + 2;
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

char	**add_quotes(char **arr, int arr_len)
{
	char	**quoted_arr;
	int		i;

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
			quoted_arr[i] = ft_strdup(arr[i]);
		i++;
	}
	return (quoted_arr);
}

char	**take_variables(char **arr)
{
	char	**new_arr;
	int		i;
	char	*ptr;

	new_arr = copy_arr(arr);
	i = 0;
	while (new_arr[i])
	{
		if (new_arr[i][0])
		{
			ptr = strchr(new_arr[i], '=');
			*ptr = '\0';
		}
		i++;
	}
	return (new_arr);
}

void	sort_env(char **arr, int arr_len)
{
	char	**var_arr;
	char	*tmp_p;
	int		i;

	var_arr = take_variables(arr);
	while (arr_len-- > 0)
	{
		i = 0;
		while (i < arr_len)
		{
			if (strcmp(var_arr[i], var_arr[i + 1]) > 0)
			{
				tmp_p = var_arr[i];
				var_arr[i] = var_arr[i + 1];
				var_arr[i + 1] = tmp_p;
				tmp_p = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp_p;
			}
			i++;
		}
	}
	free_arr(var_arr);
}

int	print_sorted_env(int *fd, char **envp)
{
	int		i;
	int		envp_len;
	char	**quoted_envp;

	envp_len = count_arr_size(envp);
	quoted_envp = add_quotes(envp, envp_len);
	sort_env(quoted_envp, envp_len);
	i = 0;
	while (quoted_envp[i])
	{
		if (quoted_envp[i][0])
		{
			write(fd[OUT], ENV_PREFIX, ft_strlen(ENV_PREFIX));
			write(fd[OUT], " ", 1);
			write(fd[OUT], quoted_envp[i], ft_strlen(quoted_envp[i]));
			write(fd[OUT], "\n", 1);
		}
		i++;
	}
	free_arr(quoted_envp);
	return (0);
}

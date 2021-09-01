#include "mimibash.h"

int	count_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

char	**copy_arr(char **arr)
{
	char	**arr_copy;
	int		arr_size;
	int		i;

	arr_size = count_arr_size(arr);
	i = 0;
	arr_copy = malloc((arr_size + 1) * sizeof(char *));
	if (!arr_copy)
		error_and_exit(NULL, NULL, 1);
	while (arr[i])
	{
		arr_copy[i] = ft_strdup(arr[i]);
		if (!arr_copy[i])
			error_and_exit(NULL, NULL, 1);
		i++;
	}
	arr_copy[i] = NULL;
	return (arr_copy);
}

char	**free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (NULL);
}

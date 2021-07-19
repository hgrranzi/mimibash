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
		system_error(errno);
	while (arr[i])
	{
		arr_copy[i] = strdup(arr[i]);
		if (!arr_copy[i])
			system_error(errno);
		i++;
	}
	arr_copy[i] = NULL;
	return (arr_copy);
}

#include "mimibash.h"

int	aka_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!aka_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_data(t_data **data)
{
	t_data	*data_p;

	while (*data)
	{
		data_p = *data;
		*data = (*data)->next;
		free_arr(data_p->args);
		free(data_p);
	}
}

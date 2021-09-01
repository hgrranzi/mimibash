#include "mimibash.h"

int	only_digits(char *str)
{
	int	i;
	int	n;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	n = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || n > 19)
			return (0);
		i++;
		n++;
	}
	return (1);
}

// void	free_data(t_data **data)
// {
// 	t_data	*data_p;

// 	while (*data)
// 	{
// 		data_p = *data;
// 		*data = (*data)->next;
// 		free_arr(data_p->args);
// 		free(data_p);
// 	}
// }

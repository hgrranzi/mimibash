#include "mimibash.h"

int	only_digits(char *str)
{
	int	i;
	int	n;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (((ft_isdigit(str[0]) || str[0] == '+') && (ft_strcmp(&str[i], LONG_P) > 0))
		|| (str[0] == '-' && (ft_strcmp(&str[i], LONG_N) > 0)))
		return (0);
	n = 0;
	while (str[i])
	{
		n++;
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	fill_quote_str(char *new_str, char *str, int quote_index, int new_len)
{
	int		i;
	int		j;

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
}

int	massive_size(char **mas)
{
	int	i;

	i = 0;
	while (mas && mas[i] != NULL)
		i++;
	return (i);
}

int	ft_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

void	fill_struct(t_data *data)
{
	data->builtin = 1;
	data->args = ft_calloc(2, sizeof(char *));
	data->args[0] = ft_strdup("echo");
	data->args[1] = NULL;
}

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

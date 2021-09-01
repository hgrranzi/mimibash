#include "libft.h"

int	ft_atoi(const char *str)
{
	int			i;
	long int	d;
	int			z;

	z = 1;
	i = 0;
	d = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			z = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		d = str[i] - '0' + d * 10;
		i++;
	}
	return (d * z);
}

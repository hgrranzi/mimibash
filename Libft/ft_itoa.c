#include "libft.h"

static	int	ft_countdig(int m, int *i)
{
	int	d;

	d = 1;
	if (m < 0)
		*i = 2;
	else
		*i = 1;
	while (m > 9 || m < -9)
	{
		m /= 10;
		d = d * 10;
		(*i)++;
	}
	return (d);
}

static int	val_ret(int z)
{
	if (z < 0)
		return (-1);
	else
		return (1);
}

char	*ft_itoa(int n)
{
	int		d;
	int		i;
	int		z;
	char	*str;

	z = val_ret(n);
	d = ft_countdig(n, &i);
	str = (char *)malloc(i + 1);
	if (!str)
		return (0);
	i = 0;
	if (n < 0)
		str[i++] = '-';
	while (d > 0)
	{
		str[i++] = z * (n / d) + '0';
		n = n % d;
		d /= 10;
	}
	str[i] = '\0';
	return (str);
}

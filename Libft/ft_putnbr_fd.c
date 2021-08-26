#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		m;
	int		d;

	d = 1;
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	if (n < 0 && n != -2147483648)
	{
		write(fd, "-", 1);
		n *= (-1);
	}
	m = n;
	while (m > 0)
	{
		d = d * 10;
		m /= 10;
	}
	while (d > 0 && n != -2147483648)
	{
		c = (n / d) + '0';
		n = n % d;
		d /= 10;
		write(fd, &c, 1);
	}
}

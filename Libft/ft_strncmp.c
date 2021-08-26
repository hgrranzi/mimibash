#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				diff;
	unsigned char	*p1;
	unsigned char	*p2;

	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	if (s1 == NULL && s2 == NULL)
		return (0);
	i = 0;
	diff = 0;
	while (i < n && diff == 0)
	{
		if (p1[i] && p2[i])
		{
			diff = p1[i] - p2[i];
			i++;
		}
		else
			return (p1[i] - p2[i]);
	}
	return (diff);
}

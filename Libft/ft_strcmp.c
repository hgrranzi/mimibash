#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i])
		i++;
	if (s1[i] == '\0')
		return (0);
	return (s1[i] - s2[i]);
}

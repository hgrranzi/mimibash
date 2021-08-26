#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	i = ft_strlen(s);
	str = (char *)s;
	while (str[i] != (char)c && i > 0)
		i--;
	if (i == 0 && str[i] != c)
		return (0);
	return (str + i);
}

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	size_t	i;
	char	*s;

	i = 0;
	if (size > ft_strlen(s1))
		size = ft_strlen(s1);
	s = malloc(size + 1);
	if (s == NULL)
		return (NULL);
	while (s1[i] && i < size)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

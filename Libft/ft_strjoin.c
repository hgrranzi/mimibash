#include "libft.h"

static int	check_alloc(char **strj, int n)
{
	*strj = malloc (n + 1);
	if (!*strj)
		return (0);
	return (1);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strj;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = ft_strlen(s1) + ft_strlen(s2);
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (!check_alloc(&strj, n))
		return (NULL);
	while (s1[i] != '\0')
	{
		strj[i] = s1[i];
		i++;
	}
	while (i < n)
	{
		strj[i] = s2[j];
		i++;
		j++;
	}
	strj[i] = '\0';
	return (strj);
}

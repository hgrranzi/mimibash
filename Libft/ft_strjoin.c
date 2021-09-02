#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strj;
	int		i;
	int		j;
	int		n;

	i = 0;
	j = 0;
	n = ft_strlen(s1) + ft_strlen(s2);
	strj = malloc(n + 1);
	if (s1 && s2 && strj)
	{
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
	}
	return (strj);
}

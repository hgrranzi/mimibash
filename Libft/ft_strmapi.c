#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	int		lenstr;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	lenstr = ft_strlen(s);
	str = (char *)malloc(lenstr + 1);
	if (str == NULL)
		return (NULL);
	while (i < lenstr)
	{
		str[i] = (*f)(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

#include "libft.h"

static size_t	ft_countword(char const *s, char c)
{
	int			i;
	int			count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_wrdlen(char const *s, char c)
{
	int			i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char	**ft_free(char **s)
{
	int	i;

	i = 0;
	while (*s)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	str = (char **)ft_calloc((ft_countword(s, c) + 1), sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			str[j++] = ft_substr((s + i), 0, ft_wrdlen(s + i, c));
			if (!str)
				return (ft_free(str));
			i += ft_wrdlen(s + i, c);
		}
	}
	str[j] = 0;
	return (str);
}

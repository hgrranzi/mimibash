#include "mimibash.h"

static size_t	ft_countword(char const *s, char c)
{
	int			i;
	int			k;
	int			n;
	int			count;

	i = 0;
	k = 0;
	n = 0;
	count = 0;
	while (s[i] != '\0')
	{
		check_open_quote(s[i], &n, &k, &i);
		if((k%2) == 0 && (n%2) == 0)
		{
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
				count++;
		}
		i++;
	}
	count += k / 2 - 1;
	return (count);
}

static size_t	ft_wrdlen(char const *s, char c)
{
	int			i;
	int			k;
	int			n;

	i = 0;
	k = 0;
	n = 0;
	while (s[i] != '\0')
	{
		check_open_quote(s[i], &n, &k, &i);
		if((k%2) == 0 && (n%2) == 0)
		{
			while(s[i] != c && s[i] != '\0')
				i++;
			return (i);
		}
		else
		{
			while(s[i] != '\"' && s[i] != '\0')
				i++;
			return (i + 1);
		}
		i++;
	}
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

char	**new_splitn(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	str = (char **)ft_calloc((ft_countword(s, c) + 2), sizeof(char *));
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
	str[j++] = "\n";
	str[j] = NULL;
	return (str);
}
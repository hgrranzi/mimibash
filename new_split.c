#include "mimibash.h"

static size_t	ft_countword(char const *s, char c)
{
	int	i;
	int	k;
	int	n;
	int	count;

	i = 0;
	k = 0;
	n = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
			skip_quote(s, &i, '\"');
		if (s[i] == '\'')
			skip_quote(s, &i, '\'');
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static size_t	ft_wrdlen(char const *s, char c)
{
	int	i;
	int	k;
	int	n;

	i = 0;
	k = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"')
			skip_quote(s, &i, '\"');
		if (s[i] == '\'')
			skip_quote(s, &i, '\'');
		if (s[i] == c || s[i] == '\0')
			break;
		i++;
	}
	return (i);
}

char	**new_split(char const *s, char c)
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
				return (free_arr(str));
			i += ft_wrdlen(s + i, c);
		}
	}
	str[j] = NULL;
	return (str);
}

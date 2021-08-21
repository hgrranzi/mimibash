#include "mimibash.h"

void	skip_quote(char const *str, int *i, char c)
{
	while (str[++(*i)] != '\0')
	{
		if (str[(*i)] == c)
			break ;
	}
}

int	countpipe(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			skip_quote(str, &i, '\"');
		if (str[i] == '\'')
			skip_quote(str, &i, '\'');
		if (str[i] != '|' && (str[i + 1] == '|' || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

int	pipelen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"')
			skip_quote(str, &i, '\"');
		if (str[i] == '\'')
			skip_quote(str, &i, '\'');
		if (str[i] == '|')
			break ;
		i++;
	}
	return (i);
}

char	**pipesplit(char *str)
{
	int		i;
	int		j;
	int		m;
	char	**tmp;

	i = 0;
	j = 0;
	m = countpipe(str);
	tmp = (char **)ft_calloc((m + 1), sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] == '|')
			i++;
		if (str[i] != '\0')
		{
			tmp[j++] = ft_substr((str + i), 0, pipelen(str + i));
			if (!tmp)
				return (free_arr(tmp));
			i += pipelen(str + i);
		}
	}
	tmp[j] = NULL;
	return (tmp);
}

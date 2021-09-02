#include "mimibash.h"

char	*getstrquote(char *str, int i, int j)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	tmp1 = ft_substr(str, 0, i);
	tmp2 = ft_substr(str, i + 2, j - i - 2);
	tmp3 = ft_strdup(str + j + 1);
	tmp4 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	tmp1 = NULL;
	free(tmp2);
	tmp2 = NULL;
	tmp1 = ft_strjoin(tmp4, tmp3);
	free(tmp4);
	tmp4 = NULL;
	free(tmp3);
	tmp3 = NULL;
	return (tmp1);
}

char	*parse_dollar_quote(char *str, int *i)
{
	int		j;
	char	*tmp1;

	j = (*i);
	(*i) += 2;
	while (str[++(*i)] != '\0')
	{
		if (str[(*i)] == '\"')
			break ;
	}
	if (str[(*i)] == '\0')
	{
		error_and_exit(NULL, ERR_SYNTAX, 0);
		free(str);
		str = NULL;
		return (ft_strdup("258"));
	}
	else
		tmp1 = getstrquote(str, j, (*i));
	free(str);
	str = NULL;
	(*i) = (*i) - 2;
	return (tmp1);
}

void	check_dollar(char **str, char **env)
{
	int	i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\'')
			skip_quote(*str, &i, '\'');
		if ((*str)[i] == '$' && ft_key((*str)[i + 1]))
			(*str) = parse_dollar((*str), &i, env);
		if ((*str)[i] == '$' && (*str)[i + 1] == '\"')
			(*str) = parse_dollar_quote((*str), &i);
		i++;
	}
}

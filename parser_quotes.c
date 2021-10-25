#include "mimibash.h"

int	get_from_env(char **getstr, char *env, char *str, char **str2)
{
	int		n;
	char	*tmp;

	n = ft_strlen(str);
	tmp = ft_strnstr(env, str, n);
	if (tmp)
	{
		(*getstr) = ft_strjoin((*str2), tmp + n);
		free(*str2);
		*str2 = NULL;
		return (ft_strlen(tmp + n) - 1);
	}
	return (0);
}

char	*parse_single_quote(char *str, int *i)
{
	int		j;
	char	*tmp1;

	j = (*i);
	while (str[++(*i)] != '\0')
	{
		if (str[(*i)] == '\'')
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
		tmp1 = getstr(str, j, (*i));
	free(str);
	str = NULL;
	(*i)--;
	return (tmp1);
}

#include "mimibash.h"
char *parse_slash(char *str, int *i)
{
	char *tmp1;
	char *tmp2;
	char *tmp3;

	tmp1 = ft_substr(str, 0, (*i));
	tmp2 = ft_strdup(str + (*i) + 1);
	tmp3 = ft_strjoin(tmp1, tmp2);
	free(tmp2);
	free(tmp1);
	free(str);
	(*i)++;
	return (tmp3);
}
char *getstr(char *str, int i, int j)
{
	char *tmp1;
	char *tmp2;
	char *tmp3;
	char *tmp4;

	tmp1 = ft_substr(str, 0, i);
	tmp2 = ft_substr(str, i + 1, j - i - 1);
	tmp3 = ft_strdup(str + j + 1);
	tmp4 = ft_strjoin(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	tmp1 = ft_strjoin(tmp4, tmp3);
	free(tmp4);
	free(tmp3);
	return(tmp1);
}
char *parse_single_quote(char *str, int *i)
{
	int j;
	char *tmp1;

	j = (*i);
	while (str[++(*i)] != '\0')
	{
		if (str[(*i)] == '\'')
			break;
	}
	if (str[(*i)] == '\0')
	{
		write(1, "syntax error: single quotes are not closed\n", 43);
		free(str);
		return(ft_strdup("\0"));
	}
	else
		tmp1 = getstr(str, j, (*i));
	free(str);
	(*i) = (*i) - 2;
	return (tmp1);
}
char *parse_double_quote(char *str, int *i, char **env)
{
	int j;
	char *tmp1;

	j = (*i);
	while (str[++(*i)] != '\0')
	{
		if (str[(*i)] == '\\' && ((str[(*i) + 1] == '\'') || (str[(*i) + 1] == '\"') || (str[(*i) + 1] == '$') || (str[(*i) + 1] == '\\')))
			str = parse_slash(str, i);
		if (str[(*i)] == '$' && ft_key(str[(*i) + 1]))
			str = parse_dollar(str, i, env);
		if (str[(*i)] == '\"')
			break;
	}
	if (str[(*i)] == '\0')
	{
		write(1, "syntax error: double quotes are not closed\n", 43);
		free(str);
		return(ft_strdup("\0"));
	}
	else
		tmp1 = getstr(str, j, (*i));
	free(str);
	(*i) = (*i) - 2;
	return (tmp1);
}
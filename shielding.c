#include "mimibash.h"

void	spec_free(char **str1, char **str2, char **str3)
{
	free(*str1);
	*str1 = NULL;
	free(*str2);
	*str2 = NULL;
	free(*str3);
	*str3 = NULL;
}

char	*unpack(char *str, char **env, char *str2)
{
	int		n;
	int		i;
	char	*tmp;
	char	*getstr;

	i = 0;
	n = ft_strlen(str);
	while (env[i] != NULL)
	{
		tmp = ft_strnstr(env[i], str, n);
		if (tmp)
		{
			getstr = ft_strjoin(str2, tmp + n);
			free(str2);
			str2 = NULL;
			free(str);
			str = NULL;
			break ;
		}
		i++;
	}
	return (getstr);
}

char	*parse_dollar(char *str, int *i, char **env)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	int		j;

	j = (*i);
	while (str[++(*i)] != '\0' )
	{
		if (!ft_key(str[(*i)]))
			break ;
	}
	tmp1 = ft_substr(str, j + 1, (*i) - j - 1);
	tmp2 = ft_substr(str, 0, j);
	tmp4 = ft_strdup(str + (*i));
	tmp3 = ft_strjoin(tmp1, "=");
	free(tmp1);
	tmp2 = unpack(tmp3, env, tmp2);
	tmp3 = ft_strjoin(tmp2, tmp4);
	spec_free(&tmp2, &tmp4, &str);
	return (tmp3);
}

char	*parse_exitcode(char *str, int *i, int exit_code)
{
	int		j;
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	tmp1 = ft_substr(str, 0, (*i));
	tmp2 = ft_strdup(str + (*i) + 2);
	tmp3 = ft_itoa(exit_code);
	tmp4 = ft_strjoin(tmp1, tmp3);
	free(tmp1);
	free(tmp3);
	tmp1 = ft_strjoin(tmp4, tmp2);
	free(tmp4);
	free(tmp2);
	free(str);
	return (tmp1);
}
// char *parse_star(char *str, int *i)
// {

// }
char	**shielding(char **str, char **env, int exit_status)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			// if (str[i][j] == '*')
			// 	str[i] = parse_star(str[i], &j);
			if (str[i][j] == '$' && str[i][j + 1] == '?')
				str[i] = parse_exitcode(str[i], &j, exit_status);
			if (str[i][j] == '$' && ft_key(str[i][j + 1]))
				str[i] = parse_dollar(str[i], &j, env);
			if (str[i][j] == '\\')
				str[i] = parse_slash(str[i], &j);
			if (str[i][j] == '\'')
				str[i] = parse_single_quote(str[i], &j);
			if (str[i][j] == '\"')
				str[i] = parse_double_quote(str[i], &j, env);
			j++;
		}
		i++;
	}
	return (str);
}

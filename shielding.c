#include "mimibash.h"

void	spec_free(char **str1, char **str2, char **str3)
{
	if (*str1)
	{	
		free(*str1);
		*str1 = NULL;
	}
	if (*str2)
	{
		free(*str2);
		*str2 = NULL;
	}
	if (*str3)
	{
		free(*str3);
		*str3 = NULL;
	}
}

char	*unpack(char **str, char **env, char *str2, int *j)
{
	int		n;
	int		i;
	char	*tmp;
	char	*getstr;

	i = 0;
	n = ft_strlen((*str));
	getstr = NULL;
	while (env[i] != NULL)
	{
		tmp = ft_strnstr(env[i], (*str), n);
		if (tmp)
		{
			getstr = ft_strjoin(str2, tmp + n);
			free(str2);
			str2 = NULL;
			(*j) += ft_strlen(tmp + n) - 1;
			break ;
		}
		i++;
	}
	free((*str));
	str = NULL;
	if (!getstr)
		return(str2);
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
	while (str[++j] != '\0' )
	{
		if (!ft_key(str[j]))
			break ;
	}
	tmp1 = ft_substr(str, (*i) + 1, (j) - (*i) - 1);
	tmp2 = ft_substr(str, 0, (*i));
	tmp4 = ft_strdup(str + j);
	tmp3 = ft_strjoin(tmp1, "=");
	free(tmp1);
	tmp2 = unpack(&tmp3, env, tmp2, i);
	tmp3 = ft_strjoin(tmp2, tmp4);
	(*i)--;
	spec_free(&tmp2, &tmp4, &str);
	return (tmp3);
}

char	*parse_exitcode(char *str, int *i, int exit_code)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	tmp1 = ft_substr(str, 0, (*i));
	tmp2 = ft_strdup(str + (*i) + 2);
	tmp3 = ft_itoa(exit_code);
	tmp4 = ft_strjoin(tmp1, tmp3);
	free(tmp1);
	tmp1 = NULL;
	free(tmp3);
	tmp3 = NULL;
	tmp1 = ft_strjoin(tmp4, tmp2);
	free(tmp4);
	tmp4 = NULL;
	free(tmp2);
	tmp2 = NULL;
	free(str);
	str = NULL;
	return (tmp1);
}

char	**shielding(char **str, char **env, int exit_status)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] != NULL)
	{
		j = 0;
		while (str[i][j] != '\0')
		{
			if (str[i][j] == '$' && str[i][j + 1] == '?')
				str[i] = parse_exitcode(str[i], &j, exit_status);
			if (str[i][j] == '$' && ft_key(str[i][j + 1]))
				str[i] = parse_dollar(str[i], &j, env);
			if (str[i][j] == '\\')
				str[i] = parse_slash(str[i], &j);
			if (str[i][j] == '\'')
				str[i] = parse_single_quote(str[i], &j);
			if (str[i][j] == '\"')
				str[i] = parse_double_quote(str[i], &j, env, exit_status);
			j++;
		}
		i++;
	}
	return (str);
}

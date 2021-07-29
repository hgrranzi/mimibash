#include "mimibash.h"

int ft_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return(1);
	return (0);
}
char *parse_single_quote(char *str, int *i)
{
	int j;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	j = *i;
	while(str[++(*i)] != '\0')
	{
		if (str[(*i)] == '\'')
			break;
	}
	if (str[(*i)] == '\0')
	{
		write(1, "Syntax error: single quotes are not closed\n", 43);
		return("err");
	}
	tmp1 = ft_substr(str, 0, j );
	tmp2 = ft_substr(str, j + 1, (*i) - j - 1);
	tmp3 = ft_strdup(str + (*i) + 1);
	tmp1 = ft_strjoin(tmp1, tmp2);
	free(tmp2);
	tmp1 = ft_strjoin(tmp1, tmp3);
	free(tmp3);
	free(str);
	(*i)--;
	return (tmp1);
}

char *parse_slash(char *str, int *i)
{
	char *tmp1;
	char *tmp2;

	tmp1 = ft_substr(str, 0, (*i));
	tmp2 = ft_strdup(str + (*i) + 1);
	tmp1 = ft_strjoin(tmp1, tmp2);
	free(tmp2);
	free(str);
	(*i)++;
	return (tmp1);
}
char *parse_dollar(char *str, int *i, char **env)
{
	char *tmp1;
	char *tmp2;
	char *tmp3;
	char *tmp4;
	int j;
	int n;
	int k;
	int m;

	k = 0;
	j = (*i);
	while(str[++(*i)] != '\0' )
	{
		if (!ft_key(str[(*i)]))
			break;
	}
	tmp1 = ft_substr(str, j + 1, (*i) - j - 1);
	tmp2 = ft_substr(str, 0, j);
	tmp4 = ft_strdup(str + (*i));
	tmp1 = ft_strjoin(tmp1, "=");
	n = ft_strlen(tmp1);
	while (env[k] != NULL)
	{
		if ((tmp3 = ft_strnstr(env[k], tmp1, n)))
			tmp2 = ft_strjoin(tmp2, tmp3 + n);
		k++;
	}
	free(tmp1);
	free(tmp3);
	tmp2 = ft_strjoin(tmp2, tmp4);
	free (tmp4);
	return (tmp2);
}

char *parse_double_quote(char *str, int *i, char **env)
{
	int j;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	j = *i;
	while(str[++(*i)] != '\0')
	{
		if (str[(*i)] == '\\' && (str[(*i)+1] == '\"' || str[(*i)+1] == '\\' || str[(*i)+1] == '$'))
			str = parse_slash(str, i);
		if (str[(*i)] == '$')
			str = parse_dollar(str, i, env);
		if (str[(*i)] == '\"')
			break;
	}
	if (str[(*i)] == '\0')
	{
		// error_and_exit(NULL, ERR_SYNTAX, 0);
		write(1, "syntax error: double quotes are not closed\n", 43);

		return("err");
	}
	else
	{
		tmp1 = ft_substr(str, 0, j);
		tmp2 = ft_substr(str, j + 1, (*i) - j - 1);
		tmp3 = ft_strdup(str + (*i) + 1);
		tmp1 = ft_strjoin(tmp1, tmp2);
		free(tmp2);
		tmp1 = ft_strjoin(tmp1, tmp3);
		free(tmp3);
		free(str);
		(*i)--;
		return (tmp1);
	}
}

char **shielding(char **input, char **envp)
{
	int i;
	int j;

	i = 0;
	while (input[i] != NULL)
	{
		j = 0;
		while(input[i][j] !='\0')
		{
			
			if (input[i][j] == '$')
				input[i] = parse_dollar(input[i], &j, envp);
			if (input[i][j] == '\\')
				input[i] = parse_slash(input[i], &j);
			if (input[i][j] == '\'')
				input[i] = parse_single_quote(input[i], &j);
			if (input[i][j] == '\"')
				input[i] = parse_double_quote(input[i], &j, envp);
			j++;
			
		}
		// printf("%s\n", input[i]);
		i++;
	}
	return (input);
}

void parser(char *input, char **envp, t_data *data)
{
	int i;
	int j;
	char **str;
	char **tmp;
	i = 0;
	j = -1;
	str = new_split(input, '|');
	free(input);
	while(str[i] !=NULL)
	{
		add_back_lst(&data, newlst());
		str[i] = parse_redir(str[i], data->fd, envp);
		tmp = new_split(str[i], ' ');
		tmp = shielding(tmp, envp);
		// while(tmp[++j] != NULL)
		//  	printf("tmp[%d]:%s\n", j, tmp[j]);
		// get_builtins(tmp[0], &data->builtin);
		free(tmp);
		i++;
	}
	// return (str);
}

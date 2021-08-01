#include "mimibash.h"
int create_fd(char *str, int flag, int *old_fd)
{
	int fd;

	if (flag == 1)
	{
		if (*old_fd > 1)
			close(*old_fd);
		fd = open(str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	if (flag == 2)
	{
		if (*old_fd > 1)
			close(*old_fd);
		fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (flag == 3)
	{
		if (*old_fd > 0)
			close(*old_fd);
		fd = open(str, O_RDONLY, 0644);
	}
	if (fd == -1)
		error_and_exit(str, NULL, 0);	
	return (fd);
}

char *redir(char *str, int *i, int *fd, int flag, char **env)
{
	int j;
	int n;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	j = (*i);
	(*i)++;
	while (str[(*i)] == ' ')
		(*i)++;
	n = (*i) - j;
	while(str[(*i)] != '\0' )
	{
		if (str[(*i)] == '$')
			str = parse_dollar(str, i, env);
		if (str[(*i)] == '\"')
			str = parse_double_quote(str, i, env);
		if (str[(*i)] == '\'')
			str = parse_single_quote(str, i);
		if (!ft_key(str[(*i)]))
			break;
		(*i)++;
	}
	tmp1 = ft_substr(str, 0, j);
	tmp2 = ft_substr(str, j + n, (*i) - j - 2);
	tmp3 = ft_strdup(str + (*i));
	tmp1 = ft_strjoin(tmp1, tmp3);
	(*fd) = create_fd(tmp2, flag, fd);
	if((*fd) == -1)
	{
		free(tmp2);
		tmp2 = NULL;
	}
	free(tmp3);
	(*i)= j - 1;
	return(tmp1);

}
void check_open_quote(char c, int *n, int *k, int *i)
{
	if (c == '\"' && (*n)%2 == 0)
	{
		(*k)++;
		(*i)++;
	}
	if (c == '\'' && (*k)%2 == 0)
	{
		(*n)++;
		(*i)++;
	}
}
char *double_quote_redir(char *str, int *i)
{
	int j;
	char *tmp1;
	char *tmp2;
	char *tmp3;

	j = *i;
	while(str[++(*i)] != '\0')
	{
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
char *heredoc(char *str, int *i, int *fd)
{
	int j;
	int n;

	j = (*i);
	(*i)++;
	while (str[(*i)] == ' ')
		(*i)++;
	n = (*i) - j;
	while(str[(*i)] != '\0' )
	{
		if (str[(*i)] == '\"')
			str = double_quote_redir(str, i);
		if (str[(*i)] == '\'')
			str = parse_single_quote(str, i);
		if (!ft_key(str[(*i)]))
			break;
		(*i)++;
	}
}
char *parse_redir(char *str, int *fd, char **envp)
{
	int i;
	int k;
	int n;

	i = 0;
	k = 0;
	n = 0;
	while(str[i] != '\0' && fd[0] != -1 && fd[1] != -1)
	{
		check_open_quote(str[i], &n, &k, &i);
		if((k%2) == 0 && (n%2) == 0)
		{
			if(str[i] == '>' && str[i + 1] == '>')
				str = redir(str, (&i + 1), &fd[1], 1, envp);
			if (str[i] == '>' && str[i + 1] != '>')
				str = redir(str, &i, &fd[1], 2, envp);
			if (str[i] == '<' && str[i + 1] != '<')
				str = redir(str, &i, &fd[0], 3, envp);
			// if (str[i] == '<' && str[i + 1] == '<')
			// 	str = heredoc(str, &i, &fd[0]);
		}
		i++;
	}
	return (str);
}

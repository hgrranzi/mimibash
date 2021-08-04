#include "mimibash.h"
int create_fd(char *str, int flag, int **old_fd)
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
char *fill_redir(int flag, int j, int n, t_redir *red)
{
	char *tmp1;
	char *tmp2;
	char *tmp3;
	char *tmp4;

	tmp1 = ft_substr(*red->str, 0, j);
	tmp2 = ft_substr(*red->str, j + n, red->i - n - 1);
	tmp3 = ft_strdup(*red->str + red->i + 1);
	free(*red->str);
	tmp4 = ft_strjoin(tmp1, tmp3);
	free(tmp1);
	free(tmp3);
	if (flag > 2)
		red->fd[0] = create_fd(tmp2, flag, &red->fd[0]);
	else if (flag < 3)
		red->fd[1] = create_fd(tmp2, flag, &red->fd[1]);
	return (tmp4);
}
char *redir(t_redir *red, int flag)
{
	int j;
	int n;
	char *tmp1;

	j = (red->i);
	(red->i)++;
	while (red->str[(red->i)] == ' ')
		(red->i)++;
	n = (red->i) - j;
	printf("str: %s\n", red->str);
	printf("i: %d\n", red->i);
	if (red->str[(red->i)] == '\0')
	{
		write(1, "syntax error near unexpected token \'newline\'", 43);
		return (NULL);
	}
	while(red->str[(red->i)] != '\0' )
	{
		if (red->str[(red->i)] == '$')
			red->str = parse_dollar(red->str, red->i, red->env);
		if (red->str[(red->i)] == '\"')
			red->str = parse_double_quote(red->str, red->i, red->env);
		if (red->str[(red->i)] == '\'')
			red->str = parse_single_quote(red->str, red->i);
		if (red->str[(red->i)] == ' ' || red->str[(red->i)] == '\0')
			break;
		(red->i)++;
	}
	printf("i: %d\n", red->i);
	tmp1 = fill_redir(flag, j, n, red);
	(red->i)= j - 1;
	return(tmp1);
}
// int check_open_quote(char c, int *n, int *k, int *i)
// {
// 	if (c == '\"' && *n == 0)
// 	{
// 		if ((*k) == 0)
// 		{
// 			(*k)++;
// 			return(1);
// 		}
// 		else
// 		{
// 			(*k)--;
// 			(*i)++;
// 		}
// 		(*i)++;
// 	}
// 	if (c == '\'' && (*k) == 0)
// 	{
// 		if ((*n) == 0)
// 		{
// 			(*n)++;
// 			return (1);
// 		}
// 		else
// 		{
// 			(*n)--;
// 			(*i)++;
// 		}
// 		(*i)++;
// 	}
// 	return (0);
// }
// char *double_quote_redir(char *str, int *i)
// {
// 	int j;
// 	char *tmp1;
// 	char *tmp2;
// 	char *tmp3;

// 	j = *i;
// 	while(str[++(*i)] != '\0')
// 	{
// 		if (str[(*i)] == '\"')
// 			break;
// 	}
// 	if (str[(*i)] == '\0')
// 	{
// 		// error_and_exit(NULL, ERR_SYNTAX, 0);
// 		write(1, "syntax error: double quotes are not closed\n", 43);

// 		return("err");
// 	}
// 	else
// 	{
// 		tmp1 = ft_substr(str, 0, j);
// 		tmp2 = ft_substr(str, j + 1, (*i) - j - 1);
// 		tmp3 = ft_strdup(str + (*i) + 1);
// 		tmp1 = ft_strjoin(tmp1, tmp2);
// 		free(tmp2);
// 		tmp1 = ft_strjoin(tmp1, tmp3);
// 		free(tmp3);
// 		free(str);
// 		(*i)--;
// 		return (tmp1);
// 	}
// }
// char *heredoc(char *str, int *i, int *fd)
// {
// 	int j;
// 	int n;

// 	j = (*i);
// 	(*i)++;
// 	while (str[(*i)] == ' ')
// 		(*i)++;
// 	n = (*i) - j;
// 	while(str[(*i)] != '\0' )
// 	{
// 		if (str[(*i)] == '\"')
// 			str = double_quote_redir(str, i);
// 		if (str[(*i)] == '\'')
// 			str = parse_single_quote(str, i);
// 		if (!ft_key(str[(*i)]))
// 			break;
// 		(*i)++;
// 	}
// }
char *parse_redir(char *str, int *fd, char **envp)
{
	t_redir red;

	red.i = 0;
	red.str = str;
	red.fd = fd;
	red.env = envp;
	while(str[red.i] != '\0' && fd[0] != -1 && fd[1] != -1)
	{
		if (red.str[red.i] == '\"')
			skip_quote(red.str, &red.i, '\"');
		if (red.str[red.i] == '\'')
			skip_quote(red.str, &red.i, '\'');
		if(red.str[red.i] == '>' && red.str[red.i + 1] == '>')
			red.str = redir(&red, 1);
		if (str[red.i] == '>' && str[red.i + 1] != '>')
			red.str = redir(&red, 2);
		if (str[red.i] == '<' && str[red.i + 1] != '<')
			red.str = redir(&red, 3);
		// if (str[i] == '<' && str[i + 1] == '<')
		// 	str = heredoc(str, &i, &fd[0]);
		red.i++;
	}
	return (str);
}

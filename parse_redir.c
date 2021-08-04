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
char *fill_redir(int flag, int j, int n, t_redir *red)
{
	char *tmp1;
	char *tmp2;
	char *tmp3;
	char *tmp4;

	tmp1 = ft_substr(red->str, 0, j);
	tmp2 = ft_substr(red->str, n, red->i - n);
	tmp3 = ft_strdup(red->str + red->i);
	free(red->str);
	tmp4 = ft_strjoin(tmp1, tmp3);
	free(tmp1);
	free(tmp3);
	if (flag > 2)
		red->fd[0] = create_fd(tmp2, flag, &red->fd[0]);
	else if (flag < 3)
		red->fd[1] = create_fd(tmp2, flag, &red->fd[1]);
	return (tmp4);
}
void skip_space(t_redir *red)
{
	red->i++;
	while (red->str[red->i] == ' ')
		red->i++;
}
void parse_red(t_redir *red)
{
	while(red->str[(red->i)] != '\0' )
	{
		if (red->str[(red->i)] == '$')
			red->str = parse_dollar(red->str, &red->i, red->env);
		if (red->str[(red->i)] == '\"')
			red->str = parse_double_quote(red->str, &red->i, red->env);
		if (red->str[(red->i)] == '\'')
			red->str = parse_single_quote(red->str, &red->i);
		if (red->str[(red->i)] == ' ' || red->str[(red->i)] == '\0' || red->str[(red->i)] == '>' || red->str[(red->i)] == '<')
			break;
		(red->i)++;
	}
}
char *append_output(t_redir *red, int flag)
{
	int j;
	int n;
	char *tmp;

	j = red->i;
	red->i++;
	skip_space(red);
	n = red->i;
	if (red->str[(red->i)] == '\0' || red->str[(red->i)] == '>')
	{
		write(1, "syntax error near unexpected token \'newline\'", 43);
		return (NULL);
	}
	parse_red(red);
	tmp = fill_redir(flag, j, n, red);
	(red->i)= j - 1;
	return(tmp);
}
char *redir(t_redir *red, int flag)
{
	int j;
	int n;
	char *tmp1;

	j = (red->i);
	skip_space(red);
	n = (red->i);
	if (red->str[(red->i)] == '\0')
	{
		write(1, "syntax error near unexpected token \'newline\'", 43);
		return (NULL);
	}
	parse_red(red);
	tmp1 = fill_redir(flag, j, n, red);
	(red->i)= j - 1;
	return(tmp1);
}
// void parse_heredoc(t_redir *red)
// {
// 	while(red->str[(red->i)] != '\0' )
// 	{
// 		if (red->str[(red->i)] == '\"')
// 			red->str = parse_double_quote(red->str, &red->i, red->env);
// 		if (red->str[(red->i)] == '\'')
// 			red->str = parse_single_quote(red->str, &red->i);
// 		if (red->str[(red->i)] == ' ' || red->str[(red->i)] == '\0' || red->str[(red->i)] == '>' || red->str[(red->i)] == '<')
// 			break;
// 		(red->i)++;
// 	}
// }
// char *fill_heredoc(t_redir *red, int j, int n)
// {
// 	char *tmp1;
// 	char *tmp2;
// 	char *tmp3;
// 	char *tmp4;
// 	char *str;
// 	int i;
// 	int fd;

// 	tmp1 = ft_substr(red->str, 0, j);
// 	tmp2 = ft_substr(red->str, n, red->i - n);
// 	tmp3 = ft_strdup(red->str + red->i);
// 	free(red->str);
// 	tmp4 = ft_strjoin(tmp1, tmp3);
// 	free(tmp1);
// 	free(tmp3);

// 	fd = open(".heredoc", O_RDWR | O_CREAT | O_APPEND, 0644);
// 	while (1)
// 	{
// 		str = readline(">");

// 		if (ft_strncmp(tmp2, str, (ft_strlen(tmp2) + 1)))
// 			break;
// 		i = -1;
// 		while (str[++i] !='\0')
// 			str = parse_dollar(str, &i, red->env);
		
// 	}
// 	return (tmp4);
// }
// char *heredoc(t_redir *red)
// {
// 	int j;
// 	int n;
// 	char *tmp;

// 	j = (red->i);
// 	red->i++;
// 	skip_space(red);
// 	n = (red->i);
// 	if (red->str[(red->i)] == '\0')
// 	{
// 		write(1, "syntax error near unexpected token \'newline\'", 43);
// 		return (NULL);
// 	}
// 	parse_heredoc(red);
// 	tmp = fill_heredoc(red, j, n);
// 	red->i = j - 1;
// 	return (tmp);
// }
char *parse_redir(char *str, int *fd, char **envp)
{
	t_redir red;

	red.i = 0;
	red.str = str;
	red.fd = fd;
	red.env = envp;
	while(red.str[red.i] != '\0' && fd[0] != -1 && fd[1] != -1)
	{
		if (red.str[red.i] == '\"')
			skip_quote(red.str, &red.i, '\"');
		if (red.str[red.i] == '\'')
			skip_quote(red.str, &red.i, '\'');
		if(red.str[red.i] == '>' && red.str[red.i + 1] == '>')
			red.str = append_output(&red, 1);
		if (red.str[red.i] == '>' && red.str[red.i + 1] != '>')
			red.str = redir(&red, 2);
		if (red.str[red.i] == '<' && red.str[red.i + 1] != '<')
			red.str = redir(&red, 3);
		// if (red.str[red.i] == '<' && red.str[red.i + 1] == '<')
		// 	str = heredoc(red);
		red.i++;
	}
	return (red.str);
}

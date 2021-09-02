#include "mimibash.h"

int	create_heredoc(int *old_fd)
{
	int	fd;

	if (*old_fd > 0)
		close(*old_fd);
	fd = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_and_exit(".heredoc", NULL, 0);
	return (fd);
}

void	fill_heredoc(t_redir *red, char *delimiter)
{
	char	*str;
	int		i;

	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (!ft_strncmp(delimiter, str, (ft_strlen(delimiter) + 1)))
		{
			free(str);
			break ;
		}
		i = -1;
		while (str[++i] != '\0')
		{
			if (str[i] == '$' && ft_key(str[i + 1]))
				str = parse_dollar(str, &i, red->env);
		}
		write(red->fd[0], str, ft_strlen(str));
		write(red->fd[0], "\n", 1);
		free(str);
	}
	close(red->fd[0]);
	red->fd[0] = open(".heredoc", O_RDONLY, 0644);
	unlink(".heredoc");
}

void	parse_heredoc(t_redir *red)
{
	while (red->str[(red->i)] != '\0' )
	{
		if (red->str[(red->i)] == '\"')
			red->str = parse_double_quote(red->str, &red->i, red->env, red->exit_status);
		if (red->str[(red->i)] == '\'')
			red->str = parse_single_quote(red->str, &red->i);
		if (red->str[(red->i)] == ' ' || red->str[(red->i)] == '\0'
			|| red->str[(red->i)] == '>' || red->str[(red->i)] == '<')
			break ;
		(red->i)++;
	}
}

void	make_heredoc(t_redir *red, int j, int n)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;

	tmp1 = ft_substr(red->str, 0, j);
	tmp2 = ft_substr(red->str, n, red->i - n);
	tmp3 = ft_strdup(red->str + red->i);
	free(red->str);
	tmp4 = ft_strjoin(tmp1, tmp3);
	free(tmp1);
	free(tmp3);
	red->fd[0] = create_heredoc(&red->fd[0]);
	fill_heredoc(red, tmp2);
	free(tmp2);
	tmp2 = NULL;
	red->str = ft_strdup(tmp4);
	free(tmp4);
}

void	heredoc(t_redir *red)
{
	int		j;
	int		n;

	j = (red->i);
	red->i += 2;
	skip_space(red);
	n = (red->i);
	if (red->str[(red->i)] == '\0' || red->str[(red->i)] == '<' || red->str[(red->i)] == '>')
	{
		error_and_exit(NULL, ERR_SYNTAX, 0);
		(red->i) = 2;
		free (red->str);
		red->str = NULL;
		red->str = ft_strdup("258");
		return ;
	}
	parse_heredoc(red);
	make_heredoc(red, j, n);
	red->i = j - 1;
}

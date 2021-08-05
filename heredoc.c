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
		// str = ft_strdup(":");
		str = readline("> ");
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
}

char	*heredoc(t_redir *red)
{
	int		j;
	int		n;
	char	*tmp;

	j = (red->i);
	red->i += 2;
	skip_space(red);
	n = (red->i);
	if (red->str[(red->i)] == '\0')
	{
		write(1, "syntax error near unexpected token \'newline\'", 44);
		(red->i) = 2;
		return (ft_strdup("echo"));
	}
	parse_heredoc(red);
	make_heredoc(red, j, n);
	red->i = j - 1;
	return (tmp);
}

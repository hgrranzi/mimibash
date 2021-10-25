#include "mimibash.h"

void	skip_space(t_redir *red)
{
	while (red->str[red->i] == ' ')
		red->i++;
}

int	create_fd(char *str, int flag, int *old_fd)
{
	int	fd;

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

void	check_redir(t_redir *red)
{
	if ((red->str[red->i] && red->str[red->i] == '>'
			&& red->str[(red->i + 1)] == '>'))
		red->str = append_output(red, 1);
	if (red->str[red->i] == '>' && red->str[(red->i + 1)] != '>')
		red->str = redir(red, 2);
	if (red->str[red->i] == '<' && red->str[red->i + 1] != '<')
		red->str = redir(red, 3);
	if (red->str[red->i] == '<' && red->str[red->i + 1] == '<')
		heredoc(red);
}

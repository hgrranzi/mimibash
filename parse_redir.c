#include "mimibash.h"

void	parse_red(t_redir *red)
{
	while (red->str[(red->i)] != '\0' )
	{
		if (red->str[(red->i)] == '$')
			red->str = parse_dollar(red->str, &red->i, red->env);
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

char	*append_output(t_redir *red, int flag)
{
	int		j;
	int		n;
	char	*tmp;

	j = red->i;
	red->i+=2;
	skip_space(red);
	n = red->i;
	if (red->str[(red->i)] == '\0' || red->str[(red->i)] == '>')
	{
		error_and_exit(NULL, ERR_SYNTAX, 0);
		(red->i) = 2;
		free (red->str);
		return (ft_strdup("258"));
	}
	parse_red(red);
	tmp = fill_redir(flag, j, n, red);
	(red->i) = j - 1;
	return (tmp);
}

char	*fill_redir(int flag, int j, int n, t_redir *red)
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
	if (flag > 2)
		red->fd[0] = create_fd(tmp2, flag, &red->fd[0]);
	else if (flag < 3)
		red->fd[1] = create_fd(tmp2, flag, &red->fd[1]);
	free(tmp2);
	return (tmp4);
}

char	*redir(t_redir *red, int flag)
{
	int		j;
	int		n;
	char	*tmp1;

	j = (red->i);
	red->i++;
	skip_space(red);
	n = (red->i);
	if (red->str[(red->i)] == '\0')
	{
		error_and_exit(NULL, ERR_SYNTAX, 0);
		(red->i) = 2;
		free (red->str);
		return (ft_strdup("258"));
	}
	parse_red(red);
	tmp1 = fill_redir(flag, j, n, red);
	(red->i) = j - 1;
	return (tmp1);
}

char	*parse_redir(char *str, int *fd, char **envp, int exit_status)
{
	t_redir	red;
	char	*tmp;

	red.i = 0;
	red.str = str;
	red.fd = fd;
	red.env = envp;
	red.exit_status = exit_status;
	while (red.str[red.i] != '\0' && red.fd[0] != -1 && red.fd[1] != -1)
	{
		if (red.str[red.i] && red.str[red.i] == '\"')
			skip_quote(red.str, &red.i, '\"');
		if (red.str[red.i] && red.str[red.i] == '\'')
			skip_quote(red.str, &red.i, '\'');
		if (red.str[red.i] && red.str[red.i] == '>'
			&& red.str[(red.i + 1)] == '>')
			red.str = append_output(&red, 1);
		if (red.str[red.i] == '>'
			&& red.str[(red.i + 1)] != '>')
			red.str = redir(&red, 2);
		if (red.str[red.i] == '<' && red.str[red.i + 1] != '<')
			red.str = redir(&red, 3);
		if (red.str[red.i] == '<' && red.str[red.i + 1] == '<')
			heredoc(&red);
		red.i++;
	}
	return (red.str);

}

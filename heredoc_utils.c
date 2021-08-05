#include "mimibash.h"
void	parse_heredoc(t_redir *red)
{
	while (red->str[(red->i)] != '\0' )
	{
		if (red->str[(red->i)] == '\"')
			red->str = parse_double_quote(red->str, &red->i, red->env);
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
	char	*str;

	tmp1 = ft_substr(red->str, 0, j);
	tmp2 = ft_substr(red->str, n, red->i - n);
	tmp3 = ft_strdup(red->str + red->i);
	free(red->str);
	tmp4 = ft_strjoin(tmp1, tmp3);
	free(tmp1);
	free(tmp3);
	red->fd[0] = create_heredoc(&red->fd[0]);
	fill_heredoc(red, tmp2);
	red->str = ft_strdup(tmp4);
	free(tmp4);
}

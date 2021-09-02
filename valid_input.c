#include "mimibash.h"

void	skipper(char *str, int *i)
{
	if (str)
	{
		if (str[(*i)] && str[(*i)] == ' ')
		{
			while (str[(*i)] == ' ' && str[(*i)] != '\0' )
				(*i)++;
		}
	}
}

void	check_valid(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\"')
			skip_quote((*str), &i, '\"');
		if ((*str)[i] == '\'')
			skip_quote((*str), &i, '\'');
		if ((*str)[i] && (*str)[i] == ';' )
		{
			error_and_exit(NULL, ERR_SYNTAX, 0);
			free(*str);
			*str = ft_strdup("258");
		}
		i++;
	}
}
 
void	check_pipe(char **str)
{
	int	i;

	i = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\"')
			skip_quote((*str), &i, '\"');
		if ((*str)[i] == '\'')
			skip_quote((*str), &i, '\'');
		if ((*str)[i] == '|')
		{
			i++;
			skipper(*str, &i);
			if ((*str)[i] == '|')
			{
				error_and_exit(NULL, ERR_SYNTAX, 0);
				free(*str);
				*str = ft_strdup("258");
			}
		}
		i++;
	}
}

void	valid_input(char **str)
{
	int	i;

	i = 0;
	skipper(*str, &i);
	if ((*str)[i] == '\0')
	{
		free(*str);
		*str = ft_strdup("echo -n");
	}
	if ((*str)[i] && (*str)[i] == '|' )
	{
		error_and_exit(NULL, ERR_SYNTAX, 0);
		free(*str);
		*str = ft_strdup("258");
	}
	check_pipe(str);
	check_valid(str);
}

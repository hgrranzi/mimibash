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
		if ((*str)[i] && (*str)[i + 1] && (*str)[i] == ';' && (*str)[i + 1] == ';')
		{
			error_and_exit(NULL, ERR_SYNTAX, 0);
			free(*str);
			*str = ft_strdup("echo -n");
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
		if ((*str)[i] && (*str)[i + 1] && (*str)[i] == '|' && (*str)[i + 1] != '|')
		{
			i++;
			skipper((*str), &i);
			if ((*str)[i] && (*str)[i] == '|')
			{
				error_and_exit(NULL, ERR_SYNTAX, 0);
				free(*str);
				*str = ft_strdup("echo -n");
			}
		}
		i++;
	}
}

void	valid_input(char **str)
{
	int	i;
	int	m;

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
		*str = ft_strdup("echo -n");
	}
	if ((*str)[i] && (*str)[i + 1] && (*str)[i] == '|' && (*str)[i + 1] == '|')
	{
		error_and_exit(NULL, ERR_SYNTAX, 0);
		free(*str);
		*str = ft_strdup("echo -n");
	}
	// check_pipe(str);
	check_valid(str);
}

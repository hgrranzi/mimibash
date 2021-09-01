#include "mimibash.h"

void print_struct(t_data **data) // tmp
{
	t_data *tmp;
	tmp = *data;
	while (tmp !=NULL)
	{
		printf("builtin: %d\n", tmp->builtin);
		printf("fd[0]: %d\n", tmp->fd[0]);
		printf("fd[1]: %d\n", tmp->fd[1]);
		int i = 0;
		while(tmp->args[i] != NULL)
		{
			printf("args[%d]: %s\n", i, tmp->args[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	ft_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

void	check_empty(char **str)
{
	int	i;

	i = 0;
	skipper((*str), &i);
	if ((*str)[i] == '\0')
	{
		free(*str);
		(*str) = ft_strdup("echo -n");
	}
}

void	check_echo_n(t_data *data)
{
	if (data->builtin == 1 && data->args[1] && !ft_strncmp(data->args[1], "-n", 2))
		check_echo(data);
	else if (data->builtin == 1 )
		data->args = add_n(data->args);
}

void	fill_struct(t_data *data)
{
	data->builtin = 1;
	data->args = ft_calloc(2, sizeof(char *));
	data->args[0] = ft_strdup("echo");
	data->args[1] = NULL;
}

void	parser(char **input, char **envp, t_data **data, int exit_status)
{
	int		i;
	char	**str;
	char	**tmp;
	t_data	*last;

	i = 0;
	str = NULL;
	tmp = NULL;
	last = NULL;
	valid_input(input);
	str = pipesplit(*input);
	while (str[i] != NULL)
	{
		last = add_back_lst(data, newlst());
		str[i] = parse_redir(str[i], last->fd, envp, exit_status);
		tmp = new_split(str[i], ' ');

		tmp = parse_star(tmp);
		if (tmp[0] == NULL)
		{
			fill_struct(last);
			break ;
		}
		free(str[i]);
		last->args = shielding(tmp, envp, exit_status);
		get_builtins(&last->args[0], &last->builtin);
		check_echo_n(last);
		check_builtins(last, exit_status);
		i++;
	}
	free(str);
	//print_struct(data);
}

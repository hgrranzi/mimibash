#include "mimibash.h"

void	check_echo_n(t_data *data)
{
	if (data->builtin == 1 && data->args[1]
		&& !ft_strncmp(data->args[1], "-n", 2))
		check_echo(data);
	else if (data->builtin == 1 )
		data->args = add_n(data->args);
}

char	**get_array(char **str, char **envp, t_data *last, int exit_status)
{
	char	**tmp;

	tmp = NULL;
	check_dollar(str, envp);
	(*str) = parse_redir(str, last->fd, envp, exit_status);
	tmp = new_split((*str), ' ');
	tmp = parse_star(&tmp);
	return (tmp);
}

void	fix_empty(t_data *last, char **str, char ***tmp)
{
	fill_struct(last);
	free(*str);
	*str = NULL;
	free_arr((*tmp));
}

void	parse_builtins(t_data *last, char **tmp, char **envp, int exit_status)
{
	last->args = shielding(tmp, envp, exit_status);
	get_builtins(&last->args[0], &last->builtin);
	check_echo_n(last);
	check_builtins(last, exit_status);
}

void	parser(char **input, char **envp, t_data **data, int exit_status)
{
	int		i;
	char	**str;
	char	**tmp;
	t_data	*last;

	i = -1;
	str = NULL;
	last = NULL;
	valid_input(input);
	str = pipesplit(*input);
	while (str[++i] != NULL)
	{
		last = add_back_lst(data, newlst());
		tmp = get_array(&str[i], envp, last, exit_status);
		if (tmp[0] == NULL)
			fix_empty(last, &str[i], &tmp);
		else
		{
			free(str[i]);
			str[i] = NULL;
			parse_builtins(last, tmp, envp, exit_status);
		}
	}
	free_arr(str);
}

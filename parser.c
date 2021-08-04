#include "mimibash.h"

int ft_key(char c)
{
	if (c == '_' || ft_isalnum(c))
		return(1);
	return (0);
}

void print_struct(t_data **data)
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
void arr_free(char **array)
{
	int i;
	
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
void parser(char *input, char **envp, t_data **data, int exit_status)
{
	int i;
	int j;
	int n;
	char **str;
	char **tmp;
	t_data *last;
	i = 0;
	// if (valid_input(input))
	// {
		str = pipesplit(input);
		while(str[i] !=NULL)
		{
			last = add_back_lst(data, newlst());
			str[i] = parse_redir(str[i], last->fd, envp);

			tmp = new_split(str[i], ' ');
			free(str[i]);
			last->args = shielding(tmp, envp, exit_status);
			get_builtins(&last->args[0], &last->builtin);
			if (last->builtin == 1 && last->args[1] && !ft_strncmp(last->args[1], "-n", 3))
			 	last->args = remove_n(last->args, last->builtin);
			else if (last->builtin == 1 )
				last->args = add_n(last->args, last->builtin);
			check_builtins(last);
			i++;
		}
		free(str);
	// }
	// else
	// 	fill_struct(data);
	// print_struct(data);
}

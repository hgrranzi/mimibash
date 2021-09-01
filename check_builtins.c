#include "mimibash.h"

void	check_export(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	while (data->args[i] != NULL)
	{
		j = 0;
		if (ft_isdigit(data->args[i][0]) || data->args[i][0] == '=' )
			print_export_error(data, i);
		while (data->args[i][j] != '\0' && data->args[i][j] != '=')
		{
			if (!ft_key(data->args[i][j]))
			{
				print_export_error(data, i);
				break;
			}
			j++;
		}
		i++;
	}
}

void	check_unset(t_data *data)
{
	int	i;
	int	j;

	i = 1;
	while (data->args[i] != NULL)
	{
		j = 0;
		if (ft_isdigit(data->args[i][0]))
			print_unset_error(data, i);
		while (data->args[i][j] != '\0')
		{
			if (!ft_key(data->args[i][j]))
			{
				print_export_error(data, i);
				break;
			}
			j++;
		}
		i++;
	}
}

void	check_exit(char ***args, int exit_status)
{
	char	**tmp;
	int		i;
	int		j;

	if ((*args)[1] == NULL)
	{
		tmp = malloc(sizeof(char *) * 3);
		if (tmp)
		{
			tmp[0] = ft_strdup(*args[0]);
			free((*args)[0]);
			tmp[1] = ft_itoa(exit_status);
			tmp[2] = NULL;
			*args = tmp;
		}
		else
			error_and_exit(NULL, NULL, 1);
	}
}
// int check_another_symbol()
// void check_echo(t_data *data)
// {
// 	int i;
// 	int j;

// 	i = 1;
// 	if (ft_strncmp(data->args[1], "-n", 2))
// 	{
// 		while (data->args[i] != NULL)
// 		{
// 			if (!ft_strncmp(data->args[i], "-n", 2))
// 				break;
// 			check_another_symbol(data->args[i]);
// 		}
// 	}

// }
void	check_builtins(t_data *data, int exit_status)
{
	if (data->builtin == 4)
		check_export(data);
	if (data->builtin == 5)
		check_unset(data);
	if (data->builtin == 7)
		check_exit(&data->args, exit_status);
	// if (data->builtin == 1)
	// 	check_echo(data);
}

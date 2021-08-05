#include "mimibash.h"
void	check_export(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if ((!ft_key(args[i][j]) && args[i][j] != '=') ||
			(args[i][0] && args[i][1] && args[i][0] == '=' &&
			args[i][1] == '=') ||
			(args[i][0] && ft_isdigit(args[i][0])))
			{
				free(args[i]);
				args[i] = ft_strdup("\0");
				j = -1;
			}
			if (args[i][j] == '=')
				break ;
			j++;
		}
		i++;
	}
}

void	check_unset(char **args)
{
	int	i;
	int	j;

	i = 1;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (!ft_key(args[i][j]) || (args[i][0] && ft_isdigit(args[i][0])))
			{
				free(args[i]);
				args[i] = ft_strdup("\0");
				j = -1;
			}
			j++;
		}
		i++;
	}
}

void	check_builtins(t_data *data)
{	
	if (data->builtin == 4)
		check_export(data->args);
	if (data->builtin == 5)
		check_unset(data->args);
}

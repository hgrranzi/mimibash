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
				break ;
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
				break ;
			}
			j++;
		}
		i++;
	}
}

void	print_export_error(t_data *data, int i)
{
	write(1, "export: `", 9);
	write(1, data->args[i], ft_strlen(data->args[i]));
	write(1, "': not a valid identifier\n", 26);
	free(data->args[i]);
	data->args[i] = ft_strdup("\0");
}

void	print_unset_error(t_data *data, int i)
{
	write(1, "unset: `", 8);
	write(1, data->args[i], ft_strlen(data->args[i]));
	write(1, "': not a valid identifier\n", 26);
	free(data->args[i]);
	data->args[i] = ft_strdup("\0");
}

#include "mimibash.h"
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

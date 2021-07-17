#include "mimibash.h"

void	system_error(int error_code)
{
	char	*error_message;

	error_message = strerror(error_code);
	write(2, "Program exited: ", 16);
	write(2, error_message, strlen(error_message));
	write(2, "\n", 1);
	exit(1);
}

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		system_error(errno);
	data->builtin = NO_BUILTIN;
	data->path = NULL;
	data->args = NULL;
	data->fd = 1;
	data->next = NULL;
	return (data);
}

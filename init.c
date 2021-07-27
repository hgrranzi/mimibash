#include "mimibash.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		system_error(errno);
	data->builtin = NO_BUILTIN;
	//data->path = NULL;
	data->args = NULL;
	data->fd[IN] = IN;
	data->fd[OUT] = OUT;
	data->next = NULL;
	return (data);
}

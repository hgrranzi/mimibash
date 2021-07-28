#include "mimibash.h"

t_data	*init_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		error_and_exit(NULL, NULL, 1);
	data->builtin = NO_BUILTIN;
	data->args = NULL;
	data->fd[IN] = IN;
	data->fd[OUT] = OUT;
	data->exit_status = 0;
	data->next = NULL;
	return (data);
}

void	init_builtins(int (**builtins)(int *, char **))
{
	builtins[NO_BUILTIN] = NULL; // probably need an empty or error function
	builtins[ECHO] = exec_echo;
	builtins[CD] = exec_cd;
	builtins[PWD] = exec_pwd;
	builtins[EXPORT] = exec_export;
	builtins[UNSET] = exec_unset;
	builtins[ENV] = exec_env;
	builtins[EXIT] = exec_exit;
}

pid_t	*init_pids(int cmd_count)
{
	int		i;
	pid_t	*pid;

	pid = malloc(cmd_count * sizeof(int));
	if (!pid)
		error_and_exit(NULL, NULL, 1);
	i = 0;
	while (i < cmd_count)
	{
		pid[i] = 1;
		i++;
	}
	return (pid);
}

int	**init_pipes(int cmd_count)
{
	int		i;
	int		**pipe_fd;

	pipe_fd = malloc((cmd_count - 1) * sizeof(int *));
	if (!pipe_fd)
		error_and_exit(NULL, NULL, 1);
	i = 0;
	while (i < cmd_count - 1)
	{
		pipe_fd[i] = malloc(2 * sizeof(int));
		if (!pipe_fd[i])
			error_and_exit(NULL, NULL, 1);
		if (pipe(pipe_fd[i]) == -1)
			error_and_exit(NULL, NULL, 1);
		i++;
	}
	return (pipe_fd);
}

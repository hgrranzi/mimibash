#include "mimibash.h"

int	cmd_error(char *cmd, int error_code)
{
	char	*error_message;

	error_message = strerror(error_code);
	if (cmd)
	{
		write(2, cmd, strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, error_message, strlen(error_message));
	write(2, "\n", 1);
	return (1);
}

void	init_builtin_functions(int (**builtin_functions)(int, char **))
{
	builtin_functions[NO_BUILTIN] = NULL; // probably need an empty or error function
	builtin_functions[ECHO] = exec_echo;
	builtin_functions[CD] = exec_cd;
	builtin_functions[PWD] = exec_pwd;
	builtin_functions[EXPORT] = exec_export;
	builtin_functions[UNSET] = exec_unset;
	builtin_functions[ENV] = exec_env;
	builtin_functions[EXIT] = exec_exit;
}

int	count_cmd(t_data **head_cmd)
{
	t_data	*head_data_p;
	int		i;

	head_data_p = *head_cmd;
	i = 0;
	while (head_data_p)
	{
		i++;
		head_data_p = head_data_p->next;
	}
	return (i);
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

void	distribute_fd(t_data **head_cmd, int **pipe_fd)
{
	t_data	*head_data_p;
	int		i;

	head_data_p = *head_cmd;
	i = 0;
	while (head_data_p)
	{
		if (i > 0)
		{
			if (head_data_p->fd[IN] == STDIN_FILENO)
				head_data_p->fd[IN] = pipe_fd[i - 1][IN];
		}
		if (head_data_p->next != NULL)
		{
			if (head_data_p->fd[OUT] == STDOUT_FILENO)
				head_data_p->fd[OUT] = pipe_fd[i][OUT];
		}
		head_data_p = head_data_p->next;
		i++;
	}
}

int	exec_pipes(t_data *head_data, int (**builtin_functions)(int, char **), char **envp)
{
	pid_t	*pid;
	int		**pipe_fd;
	int		cmd_count;

	cmd_count = count_cmd(head_data);
	pid = init_pids(cmd_count);
	pipe_fd = init_pipes(cmd_count);
	distribute_fd(head_data, pipe_fd);
	create_processes(head_data, cmd_count, pid, pipe_fd);
	wait_and_close(pid, pipe_fd, cmd_count);
	return (0);
}

int	exec_cmd(t_data *head_data, int (**builtin_functions)(int, char **), char **envp)
{
	t_data	*head_data_p;

	head_data_p = head_data;
	if (head_data_p->next || !head_data_p->builtin)
		return (exec_pipes(head_data, builtin_functions, envp));
	if (head_data_p->builtin)
		return(builtin_functions[head_data_p->builtin](head_data_p->fd, head_data_p->args));
	return (0);
}

#include "mimibash.h"

int	create_processes(t_data **head_data, int cmd_count, pid_t *pid, int **pipe_fd, int (**builtin_functions)(int *, char **))
{
	t_data	*head_data_p;
	int		i;

	head_data_p = *head_data;
	i = 0;
	while (i < cmd_count)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			error_and_exit(NULL, NULL, 0);
		if (pid[i] == IS_CHILD)
		{
			close_unused_pipe_fd(pipe_fd, i, cmd_count);
			duplicate_fd(head_data_p->fd);
			if (head_data_p->builtin)
				return ((builtin_functions[head_data_p->builtin](head_data_p->fd, head_data_p->args)));
			else if (head_data_p->fd[IN] == -1 || head_data_p->fd[OUT] == -1)
				return (1);
			else if (!head_data_p->args[CMD_PATH])
				return (127);
			else
			{
				execve(head_data_p->args[CMD_PATH], head_data_p->args, NULL);
				error_and_exit(NULL, NULL, 0);
				if (errno == ENOENT)
					return (127);
				else
					return (126);
			}
			return (1); // draft
		}
		head_data_p = head_data_p->next;
		i++;
	}
	return (0);
}

int	exec_pipes(t_data **head_data, int (**builtin_functions)(int *, char **), char **envp)
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

int	exec_cmd(t_data **head_data, int (**builtin_functions)(int *, char **), char **envp)
{
	t_data	*head_data_p;
	char	**possible_path;

	head_data_p = *head_data;
	if (head_data_p->builtin && !head_data_p->next)
		return ((builtin_functions[head_data_p->builtin](head_data_p->fd, head_data_p->args)));
	possible_path = take_env_path(envp);
	take_cmd_path(head_data, possible_path);
	free_arr(possible_path);
	return (exec_pipes(head_data, builtin_functions, envp));
}

#include "mimibash.h"

int	count_cmd(t_data **head_data)
{
	t_data	*head_data_p;
	int		i;

	head_data_p = *head_data;
	i = 0;
	while (head_data_p)
	{
		i++;
		head_data_p = head_data_p->next;
	}
	return (i);
}

void	distribute_fd(t_data **head_data, int **pipe_fd)
{
	t_data	*head_data_p;
	int		i;

	head_data_p = *head_data;
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

void	close_unused_pipe_fd(int **pipe_fd, int i, int cmd_count)
{
	int	j;

	j = 0;
	while (j < cmd_count - 1)
	{
		if (j != i - 1)
			close(pipe_fd[j][IN]);
		if (j != i)
			close(pipe_fd[j][OUT]);
		j++;
	}
}

void	duplicate_fd(int *fd)
{
	dup2(fd[IN], STDIN_FILENO);
	dup2(fd[OUT], STDOUT_FILENO);
	return ;
}

int	create_processes(t_data **head_data, int cmd_count, pid_t *pid, int **pipe_fd)
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
			// builtin?
			if (head_data_p->args[CMD_PATH] && head_data_p->fd[IN] != -1 && head_data_p->fd[OUT] != -1)
				execve(head_data_p->args[CMD_PATH], head_data_p->args, NULL);
			return (0); // error ?
		}
		head_data_p = head_data_p->next;
		i++;
	}
	return (0);
}

void	wait_and_close(pid_t *pid, int **pipe_fd, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pid[i], NULL, 0);
		if (i > 0)
			close(pipe_fd[i - 1][IN]);
		if (i < cmd_count - 1)
			close(pipe_fd[i][OUT]);
		i++;
	}
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

	head_data_p = *head_data;
	if (head_data_p->next || !head_data_p->builtin)
		return (exec_pipes(head_data, builtin_functions, envp));
	if (head_data_p->builtin)
		return((builtin_functions[head_data_p->builtin](head_data_p->fd, head_data_p->args)));
	return (0);
}

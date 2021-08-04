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
	if (fd[IN] != STDIN_FILENO && fd[IN] != -1)
	{
		close(STDIN_FILENO);
		if (dup2(fd[IN], STDIN_FILENO) == -1)
			error_and_exit(NULL, NULL, 0);
	}
	if (fd[OUT] != STDOUT_FILENO && fd[OUT] != -1)
	{
		close(STDOUT_FILENO);
		if (dup2(fd[OUT], STDOUT_FILENO) == -1)
			error_and_exit(NULL, NULL, 0);
	}
	return ;
}

void	wait_and_close(pid_t *pid, int **pipe_fd, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		if (i > 0)
			close(pipe_fd[i - 1][IN]);
		if (i < cmd_count - 1)
			close(pipe_fd[i][OUT]);
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	i = 0;
	while (i < cmd_count -1)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
	free(pid);

}

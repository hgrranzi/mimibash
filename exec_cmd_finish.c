#include "mimibash.h"

void	close_pipes(int **pipe_fd, int cmd_count)
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
	while (i < cmd_count - 1)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}

int	wait_and_close(pid_t *pid, int cmd_count)
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = 0;
	while (i < cmd_count)
	{
		waitpid(pid[i], &pid[i], 0);
		i++;
	}
	if (WIFSIGNALED(pid[i - 1]))
		exit_status = 128 + WTERMSIG(pid[i - 1]);
	else if (WIFEXITED(pid[i - 1]))
		exit_status = WEXITSTATUS(pid[i - 1]);
	else
		exit_status = 1;
	free(pid);
	return (exit_status);
}

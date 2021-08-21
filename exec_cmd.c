#include "mimibash.h"

int	is_error(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	create_processes(t_data **head_data, t_info *info, int (**builtins)(int *, char **, char ***), char ***envp)
{
	t_data	*head_data_p;
	int		i;

	head_data_p = *head_data;
	i = 0;
	while (i < info->cmd_count)
	{
		info->pid[i] = fork();
		if (info->pid[i] == -1)
			error_and_exit(NULL, NULL, 0);
		if (info->pid[i] == IS_CHILD)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			close_unused_pipe_fd(info->pipe_fd, i, info->cmd_count);
			duplicate_fd(head_data_p->fd);
			if (head_data_p->builtin)
			{
				builtins[head_data_p->builtin](head_data_p->fd, head_data_p->args, envp);
				exit (0);
			}
			else if (head_data_p->fd[IN] == -1 || head_data_p->fd[OUT] == -1)
				exit (1);
			else if (is_error(head_data_p->args))
				exit (127);
			else
			{
				execve(head_data_p->args[CMD_PATH], head_data_p->args, *envp);
				error_and_exit(head_data_p->args[CMD_PATH], NULL, 0);
				if (errno == ENOENT)
					exit (127);
				else
					exit (126);
			}
			exit (1); // draft
		}
		if (head_data_p->fd[IN] != IN)
			close(head_data_p->fd[IN]);
		if (head_data_p->fd[OUT] != OUT)
			close(head_data_p->fd[OUT]);
		head_data_p = head_data_p->next;
		i++;
	}
	return (0);
}

int	exec_pipes(t_data **head_data, int (**builtins)(int *, char **, char ***), char ***envp)
{
	t_info	info;
	int		exit_status;

	info.cmd_count = count_cmd(head_data);
	info.pid = init_pids(info.cmd_count);
	info.pipe_fd = init_pipes(info.cmd_count);
	distribute_fd(head_data, info.pipe_fd);
	create_processes(head_data, &info, builtins, envp);
	exit_status = wait_and_close(info.pid, info.pipe_fd, info.cmd_count);
	return (exit_status);
}

int	exec_cmd(t_data **head_data, int (**builtins)(int *, char **, char ***), char ***envp)
{
	t_data	*head_data_p;
	char	**possible_path;

	head_data_p = *head_data;
	update_underscore(head_data, envp);
	if (head_data_p->builtin && !head_data_p->next)
		return ((builtins[head_data_p->builtin](head_data_p->fd, head_data_p->args, envp)));
	possible_path = take_env_path(*envp);
	take_cmd_path(head_data, possible_path);
	free_arr(possible_path);
	return (exec_pipes(head_data, builtins, envp));
}

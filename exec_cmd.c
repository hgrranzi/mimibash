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

void	update_underscore(t_data **head_data, char ***envp)
{
	char	*last_arg;
	char	**args;
	int		i;

	i = 0;
	if ((*head_data)->next == NULL)
	{
		while ((*head_data)->args[i + 1])
			i++;
		if ((*head_data)->builtin == EXPORT)
		{
			if (i == 0)
				last_arg = strdup((*head_data)->args[i]);
			else
				last_arg = strndup((*head_data)->args[i], index_char((*head_data)->args[i], '='));
		}
		else if ((*head_data)->args[i][0] != '\n')
			last_arg = strdup((*head_data)->args[i]);
		else
			last_arg = strdup((*head_data)->args[i - 1]);
	}
	else
		last_arg = strdup("\0");
	if (last_arg == NULL)
		error_and_exit(NULL, NULL, 1);
	args = malloc(3 * sizeof(char *));
	if (!args)
		error_and_exit(NULL, NULL, 1);
	args[0] = strdup("\0");
	args[1] = aka_strjoin("_=", last_arg);
	args[2] = NULL;
	free(last_arg);
	if (!args[0] || !args[1])
		error_and_exit(NULL, NULL, 1);
	exec_export((*head_data)->fd, args, envp);
	free_arr(args);
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

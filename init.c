#include "mimibash.h"

/*t_data	*init_data(void)
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
} */

char	*update_shlvl(char *shlvl_value)
{
	char	*new_value;
	int		value;

	value = atoi(shlvl_value);
	if (value < 0)
		value = 0;
	else
		value++;
	new_value = ft_itoa(value);
	if (!new_value)
		error_and_exit(NULL, NULL, 1);
	return (new_value);
}

void	init_shlvl(char ***envp)
{
	char	*shlvl_value;
	char	*key_value;
	char	*value;

	shlvl_value = take_var(*envp, "SHLVL");
	if (!shlvl_value)
	{
		key_value = aka_strjoin("SHLVL=", "1");
		if (!key_value)
			error_and_exit(NULL, NULL, 1);
		new_place(key_value, envp);
	}
	else
	{
		value = update_shlvl(shlvl_value);
		key_value = aka_strjoin("SHLVL=", value);
		if (!key_value)
			error_and_exit(NULL, NULL, 1);
		free(value);
		find_variable("SHLVL", strlen("SHLVL"), key_value, *envp);
	}
	free(shlvl_value);
	free(key_value);
}

void	init_builtins(int (**builtins)(int *, char **, char ***))
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

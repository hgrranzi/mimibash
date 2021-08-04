#include "mimibash.h"

char	**update_path(char **env_path)
{
	int		i;
	char	*new_path;

	i = 0;
	while (env_path[i])
	{
		new_path = aka_strjoin(env_path[i], "/");
		if (!new_path)
			error_and_exit(NULL, NULL, 1);
		free(env_path[i]);
		env_path[i] = new_path;
		i++;
	}
	return (env_path);
}

char	**take_env_path(char **envp)
{
	int		i;
	char	**env_path;

	i = 0;
	env_path = NULL;
	while (envp[i])
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
		{
			env_path = split_line(&envp[i][5], ':');
			if (!env_path)
				error_and_exit(NULL, NULL, 1);
			break ;
		}
		i++;
	}
	if (!env_path)
	{
		env_path = split_line(CURRENT_DIR, ':');
		if (!env_path)
			error_and_exit(NULL, NULL, 1);
	}
	return (update_path(env_path));
}

char	*check_cmd_path(char *cmd_name, char **possible_path)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (possible_path[i])
	{
		cmd_path = aka_strjoin(possible_path[i], cmd_name);
		if (!cmd_path)
			error_and_exit(NULL, NULL, 1);
		if (access(cmd_path, F_OK) == 0)
			break ;
		else
			free(cmd_path);
		i++;
	}
	if (possible_path[i] == NULL)
	{
		error_and_exit(cmd_name, ERR_CMD, 0);
		cmd_path = strdup("\0");
	}
	return (cmd_path);
}

void	take_cmd_path(t_data **head_data, char **possible_path)
{
	int		i;
	t_data	*head_data_p;
	char	*cmd_path;

	i = 1;
	head_data_p = *head_data;
	while (head_data_p)
	{
		if (!head_data_p->builtin && !strchr(head_data_p->args[CMD_PATH], '/') && (head_data_p->args[CMD_PATH][0] != '\0'))
		{
			cmd_path = check_cmd_path(head_data_p->args[CMD_PATH], possible_path);
			free(head_data_p->args[CMD_PATH]);
			head_data_p->args[CMD_PATH] = cmd_path;
		}
		head_data_p = head_data_p->next;
	}
}

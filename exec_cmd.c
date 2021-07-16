#include "mimibash.h"

int	cmd_error(char *cmd, int error_code)
{
	char	*error_message;

	error_message = strerror(error_code);
	write(2, cmd, strlen(cmd));
	write(2, ": ", 2);
	write(2, error_message, strlen(error_message));
	write(2, "\n", 1);
	return (1);
}

char	*aka_getenv(char *key, char **envp)
{
	char	*value;
	int		key_len;
	int		i;

	value = NULL;
	key_len = strlen(key);
	i = 0;
	while (envp[i])
	{
		if (strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			value = &envp[i][key_len + 1];
			break ;
		}
		i++;
	}
	return (value);
}

int	exec_pwd(int fd, char **envp) // With aka_getenv function and envp
{
	char	*wd;

	wd = aka_getenv("PWD", envp);
	if (!wd)
		return (cmd_error("pwd", errno));
	write(fd, wd, strlen(wd));
	write(fd, "\n", 1);
	return (0);
}

/*
int	exec_pwd(int fd) // With C getenv function from stdlib.h
{
	char	*wd;

	wd = getenv("PWD");
	if (!wd)
		return (cmd_error("pwd", errno));
	write(fd, wd, strlen(wd));
	write(fd, "\n", 1);
	return (0);
}*/

int	exec_cmd(t_data *head_data, char **envp)
{
	t_data	*head_data_p;

	head_data_p = head_data;
	if (head_data_p->builtin == PWD) // this is a test, wanna try an array of pointers to functions
		return (exec_pwd(head_data_p->fd, envp));
	return (0);
}

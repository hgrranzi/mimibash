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

int	exec_pwd(int fd)
{
	char	*wd;

	wd = getcwd(NULL, 0);
	if (!wd)
		return (cmd_error("pwd", errno));
	write(fd, wd, strlen(wd));
	write(fd, "\n", 1);
	free(wd);
	wd = NULL;
	return (0);
}

int	exec_cmd(t_data *head_data, char **envp)
{
	t_data	*head_data_p;

	head_data_p = head_data;
	if (head_data_p->builtin == PWD) // this is a test, wanna try an array of pointers to functions
		return (exec_pwd(head_data_p->fd));
	return (0);
}

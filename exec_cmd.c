#include "mimibash.h"

int	cmd_error(char *cmd, int error_code)
{
	char	*error_message;

	error_message = strerror(error_code);
	if (cmd)
	{
		write(2, cmd, strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, error_message, strlen(error_message));
	write(2, "\n", 1);
	return (1);
}

void	init_builtin_functions(int (**cmd_functions)(int, char **))
{
	cmd_functions[NO_BUILTIN] = NULL; // probably need an empty or error function
	cmd_functions[ECHO] = exec_echo;
	cmd_functions[PWD] = exec_pwd;
}

int	exec_cmd(t_data *head_data, char **envp)
{
	t_data	*head_data_p;
	int		(*cmd_functions[8])(int, char **);

	head_data_p = head_data;
	init_builtin_functions(cmd_functions); // that probably should be in main
	if (head_data_p->builtin)
		return(cmd_functions[head_data_p->builtin](head_data_p->fd, head_data_p->args));
	return (0);
}

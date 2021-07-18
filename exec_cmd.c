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

void	init_builtin_functions(int (**builtin_functions)(int, char **))
{
	builtin_functions[NO_BUILTIN] = NULL; // probably need an empty or error function
	builtin_functions[ECHO] = exec_echo;
	builtin_functions[CD] = exec_cd;
	builtin_functions[PWD] = exec_pwd;
	builtin_functions[EXPORT] = exec_export;
	builtin_functions[UNSET] = exec_unset;
	builtin_functions[ENV] = exec_env;
	builtin_functions[EXIT] = exec_exit;
}

int	exec_cmd(t_data *head_data, int (**builtin_functions)(int, char **), char **envp)
{
	t_data	*head_data_p;

	head_data_p = head_data;
	if (head_data_p->builtin)
		return(builtin_functions[head_data_p->builtin](head_data_p->fd, head_data_p->args));
	return (0);
}

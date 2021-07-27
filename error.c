#include "mimibash.h"

void	system_error(int error_code)
{
	char	*error_message;

	error_message = strerror(error_code);
	write(2, "Program exited: ", 16);
	write(2, error_message, strlen(error_message));
	write(2, "\n", 1);
	exit(1);
}

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

void	error_and_exit(char *reason, char *error_message, int end)
{
	char	*system_message;

	system_message = strerror(errno);
	if (reason)
	{
		write(STDERR_FILENO, reason, strlen(reason));
		write(STDERR_FILENO, ": ", 2);
	}
	if (error_message)
		write(STDERR_FILENO, error_message, strlen(error_message));
	else
		write(STDERR_FILENO, system_message, strlen(system_message));
	write(STDERR_FILENO, "\n", 1);
	if (end)
		exit(0);
}

#include "mimibash.h"

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

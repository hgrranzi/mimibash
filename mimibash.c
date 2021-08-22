#include "mimibash.h"

void	error_and_exit(char *reason, char *error_message, int end)
{
	char	*system_message;

	system_message = strerror(errno);
	if (reason)
	{
		write(STDERR_FILENO, reason, ft_strlen(reason));
		write(STDERR_FILENO, ": ", 2);
	}
	if (error_message)
		write(STDERR_FILENO, error_message, ft_strlen(error_message));
	else
		write(STDERR_FILENO, system_message, ft_strlen(system_message));
	write(STDERR_FILENO, "\n", 1);
	if (end)
		exit(0);
}

char	*read_cmd(int new_in)
{
	int		stdin_copy;
	char	*input;

	stdin_copy = dup(STDIN_FILENO);
	dup2(new_in, STDIN_FILENO);
	input = readline(PROMPT);
	dup2(stdin_copy, STDIN_FILENO);
	close(stdin_copy);
	if (!input)
	{
		close(new_in);
		input = ft_strdup("exit");
	}
	else
		add_history(input);
	return (input);
}

void	mimibash_loop(int new_in, int (**builtins)(int *, char **, char ***), char ***envp)
{
	int		exit_status;
	char	*input;
	t_data	*head_data;

	exit_status = 0;
	head_data = NULL;
	while (1)
	{
		input = read_cmd(new_in);
		parser(&input, *envp, &head_data, exit_status);
		exit_status = exec_cmd(&head_data, builtins, envp);
		free(input);
		free_data(&head_data, free);
	}
}

#include "mimibash.h"

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
		input = strdup("exit");
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

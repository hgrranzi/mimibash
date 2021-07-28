#include "mimibash.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*head_data;
	int		(*builtins[8])(int *, char **, char **);
	char	**envp_copy;

	handle_signal();
	init_builtins(builtins);
	envp_copy = copy_arr(envp);
	head_data = init_data();
	while (1)
	{
		input = readline (PROMPT);
		if (!input) // or "exit"
			head_data->builtin = EXIT;
		else
		{
			//fill_history();
			parser(input, envp_copy, &head_data);
		}
		free(input);
		exec_cmd(&head_data, builtins, envp_copy);
		//free_data();
		;
	}
	return (0);
}

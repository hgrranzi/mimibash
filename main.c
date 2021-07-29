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
	head_data = NULL;
	//head_data = init_data(); // no need probably
	while (1)
	{
		// input = ft_strdup("echo >a > b");
		// printf("%s\n", input);
		// printf ("%d", head_data->builtin);
		input = readline (PROMPT);
		if (!input) // or "exit"
			head_data->builtin = EXIT;
		else
		{
			//fill_history();
			parser(input, envp_copy, &head_data);
		}
		printf("%s %s %s\n", head_data->args[0], head_data->args[1], head_data->args[2]);
		exec_cmd(&head_data, builtins, envp_copy);
		free(input);
		exit (0);
		//free_data();
		;
	}
	return (0);
}

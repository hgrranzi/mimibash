#include "mimibash.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*head_data;
	int		(*builtin_functions[8])(int, char **);
	char	**envp_copy;

	handle_signal();
	init_builtin_functions(builtin_functions);
	envp_copy = copy_arr(envp);
	head_data = init_data();
	while (1)
	{
		input = readline (PROMPT);
		if (!input) // or "exit"
			head_data->builtin = EXIT;
		//else
		//{
			//fill_history();
			//parse_data();
		//}
		free(input);
		exec_cmd(head_data, builtin_functions, envp);
		//free_data();
		;
	}
	return (0);
}

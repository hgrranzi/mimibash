#include "mimibash.h"

int	count_arr_size(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
		i++;
	return (i);
}

char	**copy_arr(char **envp)
{
	char	**arr_copy;
	int		arr_size;
	int		i;

	arr_size = count_arr_size(envp);
	i = 0;
	arr_copy = malloc((arr_size + 1) * sizeof(char *));
	if (!arr_copy)
		system_error(errno);
	while (envp[i])
	{
		arr_copy[i] = strdup(envp[i]);
		if (!arr_copy[i])
			system_error(errno);
		i++;
	}
	arr_copy[i] = NULL;
	return (arr_copy);
}

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

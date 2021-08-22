#include "mimibash.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*head_data;
	int		(*builtins[8])(int *, char **, char ***);
	char	**envp_copy;
	int		exit_status;
	int		new_in;
	int		stdin_copy;
	int		new_in_copy;

	rl_catch_signals = 0;
	rl_outstream = stderr;
	handle_signal();
	init_builtins(builtins);
	envp_copy = copy_arr(envp);
	init_shlvl(&envp_copy);
	head_data = NULL;
	exit_status = 0;
	new_in = STDIN_FILENO;
	if (argc > 1)
	{
		new_in = open(argv[1], O_RDONLY, 0644);
		if (new_in == -1)
			error_and_exit(argv[1], NULL, 1);
	}
	while (1)
	{
		stdin_copy = dup(STDIN_FILENO);
		dup2(new_in, STDIN_FILENO);
		input = readline(PROMPT);
		dup2(stdin_copy, STDIN_FILENO);
		close(stdin_copy);
		if (!input)
			//input = strdup("exit");
		{
			head_data = malloc(sizeof(t_data));
			head_data->builtin = EXIT;
			head_data->args = malloc(3 * sizeof (char));
			head_data->args[0] = strdup("\0");
			head_data->args[1] = ft_itoa(exit_status);
			head_data->args[2] = NULL;
			head_data->fd[IN] = IN;
			head_data->fd[OUT] = OUT;
		}
		else
		{
			add_history(input);
			parser(&input, envp_copy, &head_data, exit_status);
		}
		exit_status = exec_cmd(&head_data, builtins, &envp_copy);
		free(input);
		free_data(&head_data, free);
		if (new_in)
			close(new_in);
	}
	return (0);
}

#include "mimibash.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	*head_data;
	int		(*builtins[8])(int *, char **, char ***);
	char	**envp_copy;
	int		exit_status;
	int		fd_in;

	handle_signal();
	init_builtins(builtins);
	envp_copy = copy_arr(envp);
	init_shlvl(&envp_copy);
	head_data = NULL;
	exit_status = 0;
	fd_in = STDIN_FILENO;
	if (argc > 1)
	{
		fd_in = open(argv[1], O_RDONLY, 0644);
		if (fd_in == -1)
			error_and_exit(argv[1], NULL, 1);
	}
	//head_data = init_data(); // no need probably
	while (1)
	{
		// input = ft_strdup("echo \"123");
		// printf("%s\n", input);
		// printf ("%d", head_data->builtin);
		// read (0, input, 10);
		if (fd_in != STDIN_FILENO)
			dup2(fd_in, STDIN_FILENO);
		input = readline (PROMPT);
		if (!input) // or "exit"
		{
			head_data->builtin = EXIT;
		}
		else
		{
			add_history(input);
			//fill_history();
			parser(input, envp_copy, &head_data, exit_status);

		}
		// printf("%s %s %s\n", head_data->args[0], head_data->args[1], head_data->args[2]);
		if (fd_in != STDIN_FILENO)
			dup2(STDIN_FILENO, fd_in);
		exit_status = exec_cmd(&head_data, builtins, &envp_copy);
		free(input);
		// exit (0);
		free_data(&head_data, free);
	}
	return (0);
}

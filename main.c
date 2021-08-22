#include "mimibash.h"

int	main(int argc, char **argv, char **envp)
{
	int		(*builtins[8])(int *, char **, char ***);
	char	**envp_copy;
	int		new_in;

	rl_catch_signals = 0;
	rl_outstream = stderr;
	handle_signal();
	envp_copy = copy_arr(envp);
	init_shlvl(&envp_copy);
	init_builtins(builtins);
	new_in = STDIN_FILENO;
	if (argc > 1)
	{
		new_in = open(argv[1], O_RDONLY, 0644);
		if (new_in == -1)
			error_and_exit(argv[1], NULL, 1);
	}
	mimibash_loop(new_in, builtins, &envp_copy);
	return (0);
}

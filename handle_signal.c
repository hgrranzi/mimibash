#include "mimibash.h"

void	handle_sig_pipe(int sig_number) // Ctrl + C
{
	return ;
}

int	handle_signal_pipe(void)
{
	signal(SIGQUIT, handle_sig_pipe);
	signal(SIGINT, handle_sig_pipe);
	return (0);
}

void	handle_sigint(int sig_number) // Ctrl + C
{
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	handle_signal(void)
{
	signal(SIGQUIT, handle_sig_pipe);
	signal(SIGINT, handle_sigint);
	return (0);
}

#include "mimibash.h"

void	handle_sigterm(int sig_number) // Ctrl + D
{
	// smth with readline
	return ;
}

void	handle_sigquit(int sig_number)
{
	write(1, "\b\b", 2); // temporary
	write(1, "sigquit\n", 8);
}

void	handle_sigint(int sig_number) // Ctrl + C
{
	write(2, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int	handle_signal(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	return (0);
}

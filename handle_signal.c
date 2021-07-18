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
	write(1, "\b\b", 2); // temporary
	write(1, "sigint\n", 7);
	exit (0);
}

int	handle_signal(void)
{
	signal(SIGTERM, SIG_IGN);
	signal(SIGQUIT, handle_sigquit);
	signal(SIGINT, handle_sigint);
	return (0);
}

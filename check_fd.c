#include "mimibash.h"

void	check_fd(int *fd, int j, char **bzero)
{
	if (fd[0] == -1 || fd[1] == -1)
	{
		while ((*bzero)[j] != '\0')
		{
			(*bzero)[j] = '\0';
			j++;
		}
	}
}

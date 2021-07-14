#ifndef MIMIBASH_H
# define MIMIBASH_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

typedef struct s_data
{
	char			*cmd;
	char			**args;
	int				fd;
	struct s_data	*next;
}				t_data;

t_data	*init_data(void);
void	system_error(int error_code);

#endif

#ifndef MIMIBASH_H
# define MIMIBASH_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>

# include "builtins.h"

typedef enum e_builtin
{
	NO_BUILTIN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}			t_builtin;

typedef struct s_data
{
	int				builtin;
	char			**path;
	char			**args;
	int				fd;
	struct s_data	*next;
}				t_data;

t_data	*init_data(void);
void	system_error(int error_code);

int		exec_cmd(t_data *head_data, char **envp);

#endif

#ifndef MIMIBASH_H
# define MIMIBASH_H

typedef struct s_data
{
	char			*cmd;
	char			**args;
	int				fd;
	struct s_data	*next;
}				t_data;


#endif

#ifndef MIMIBASH_H
# define MIMIBASH_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "builtins.h"

# define PROMPT "mimibash 💬 "
# define IN 0
# define OUT 1

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
	int				fd[2];
	struct s_data	*next;
}				t_data;

int		handle_signal(void);
t_data	*init_data(void);
void	system_error(int error_code);

char	**copy_arr(char **arr);
int		count_arr_size(char **arr);

int		exec_cmd(t_data *head_data, int (**cmd_functions)(int, char **), char **envp);

void	error_and_exit(char *reason, char *error_message, int end);
int		cmd_error(char *cmd, int error_code);
void	system_error(int error_code);

#endif

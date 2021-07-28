#ifndef MINISHELL_H
#define MINISHELL_H
#include "Libft/libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
typedef struct s_data
{
	int				builtin;
	//char			**path; // no need
	char			**args; // args[0] - path to the binary, the rest are arguments
	int				fd[2];
	struct s_data	*next;
}	t_data;
void parser(char *input, char **envp, t_data **data);
char *parse_redir(char *str, int *fd);
char *parse_single_quote(char *str, int *i);
char	**new_split(char const *s, char c);
void get_builtins(char *str, int *built);
int ft_key(char c);
#endif
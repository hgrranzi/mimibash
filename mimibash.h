#ifndef MIMIBASH_H
# define MIMIBASH_H

# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "Libft/libft.h"

# include "builtins.h"

# define PROMPT "mimibash 💬 "
# define ERR_CMD "command not found"
# define ERR_SYNTAX "syntax error"
# define ERR_UNSET "not a valid identifier"
# define IN 0
# define OUT 1
# define CMD_PATH 0
# define CURRENT_DIR "."
# define IS_CHILD 0

typedef struct s_data
{
	int				builtin;
	char			**args;
	int				fd[2];
	int				exit_status;
	struct s_data	*next;
}				t_data;

typedef struct s_info
{
	pid_t	*pid;
	int		**pipe_fd;
	int		cmd_count;
}				t_info;

/* handle_signal.c */

int		handle_signal(void);

/* init.c */

t_data	*init_data(void);
void	init_builtins(int (**builtins)(int *, char **, char ***));
pid_t	*init_pids(int cmd_count);
int		**init_pipes(int cmd_count);

/* arr.c */

char	**copy_arr(char **arr);
int		count_arr_size(char **arr);
char	**free_arr(char **arr);

/* split_line.c */

char	**split_line(char *s, char c);
char	*trim_line(char *s, char c);
int		words_count(const char *s, char delimiter);
char	*aka_strjoin(char const *s1, char const *s2);
int		index_char(char *str, char c);

/* take_cmd_path.c */

char	**take_env_path(char **envp);
char	**update_path(char **env_path);
void	take_cmd_path(t_data **head_data, char **possible_path);
char	*check_cmd_path(char *cmd_name, char **possible_path);

/* exec_cmd.c */

int		exec_cmd(t_data **head_data, int (**builtins)(int *, char **, char ***), char ***envp);
int		exec_pipes(t_data **head_data, int (**builtins)(int *, char **, char ***), char ***envp);
int		create_processes(t_data **head_data, t_info *info, int (**builtins)(int *, char **, char ***), char ***envp);

/* exec_cmd_utils.c */

int		count_cmd(t_data **head_data);
void	distribute_fd(t_data **head_data, int **pipe_fd);
void	close_unused_pipe_fd(int **pipe_fd, int i, int cmd_count);
void	duplicate_fd(int *fd);
void	wait_and_close(pid_t *pid, int **pipe_fd, int cmd_count);

/* error.c */

void	error_and_exit(char *reason, char *error_message, int end);

/* utils.c */

int		aka_isdigit(int c);
int		only_digits(char *str);
// void	free_data(t_data **data);

/* */

void parser(char *input, char **envp, t_data **data);
char *parse_redir(char *str, int *fd, char **envp);
char	*parse_single_quote(char *str, int *i);
char	**new_split(char const *s, char c);
void get_builtins(char **str, int *built);
int		ft_key(char c);
t_data	*newlst(void);
t_data	*lastlst(t_data *lst);
t_data	*add_back_lst(t_data **lst, t_data *new);
char *parse_single_quote(char *str, int *i);
char *parse_slash(char *str, int *i);
char *parse_dollar(char *str, int *i, char **env);
char *parse_double_quote(char *str, int *i, char **env);
void check_open_quote(char c, int *n, int *k, int *i);
void	free_data(t_data **lst, void (*del)(void *));
char **remove_n( char **args, int built);
char	**new_splitn(char const *s, char c);
char **add_n(char **args, int builtin);
void check_unset(char ***args);
#endif

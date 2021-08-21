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
# define ERR_EXIT "numeric argument required"
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

typedef struct s_redir
{
	char	*str;
	int		*fd;
	int		i;
	char	**env;
}				t_redir;

/* handle_signal.c */

int		handle_signal(void);

/* init.c */

//t_data	*init_data(void);
void	init_shlvl(char ***envp);
char	*update_shlvl(char *shlvl_value);
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
int		wait_and_close(pid_t *pid, int **pipe_fd, int cmd_count);

/* error.c */

void	error_and_exit(char *reason, char *error_message, int end);

/* utils.c */

int		aka_isdigit(int c);
int		only_digits(char *str);
// void	free_data(t_data **data);

/* update_underscore.c */

void	update_underscore(t_data **head_data, char ***envp);
char	*take_last_arg(t_data **head_data);

/* parser.c */

void	parser(char **input, char **envp, t_data **data, int exit_status);
void	fill_struct(t_data *data);
void	check_echo_n(t_data *data);
void	check_empty(char **str);
int		ft_key(char c);

/* parse_redir.c */

char	*parse_redir(char *str, int *fd, char **envp);
char	*redir(t_redir *red, int flag);
char	*fill_redir(int flag, int j, int n, t_redir *red);
char	*append_output(t_redir *red, int flag);
void	parse_red(t_redir *red);

/* pipesplit.c */

char	**pipesplit(char *str);
int		pipelen(char *str);
int		countpipe(char *str);
void	skip_quote(char const *str, int *i, char c);

/* redir_utils.c */

int		create_fd(char *str, int flag, int *old_fd);
void	skip_space(t_redir *red);

/* new_split.c */

char	**new_split(char const *s, char c);

/* get_builtins.c */

void	get_builtins(char **str, int *built);
char	*make_same(char *str);

/* add_back_lst.c */

t_data	*newlst(void);
t_data	*lastlst(t_data *lst);
t_data	*add_back_lst(t_data **lst, t_data *new);
void	free_one(t_data *lst, void (*del)(void *));
void	free_data(t_data **lst, void (*del)(void *));

/* valid_input.c */

void	valid_input(char **str);
void	check_pipe(char **str);
void	check_valid(char **str);
void	skipper(char *str, int *i);

/* remove_n.c */

char	**remove_n( char **args, int built);
char	**add_n(char **args, int builtin);

/* */

char	*parse_single_quote(char *str, int *i);
char	*parse_single_quote(char *str, int *i);
char	*parse_slash(char *str, int *i);
char	*parse_dollar(char *str, int *i, char **env);
char	*parse_double_quote(char *str, int *i, char **env);
int		check_open_quote(char c, int *n, int *k, int *i);
char	**new_splitn(char const *s, char c);
void	check_unset(char **args);
void	check_builtins(t_data *data);
char	**shielding(char **str, char **env, int exit_status);
void	skipper(char *str, int *i);
char	*heredoc(t_redir *red);
void	make_heredoc(t_redir *red, int j, int n);
void	parse_heredoc(t_redir *red);
void	fill_heredoc(t_redir *red, char *delimiter);
int		create_heredoc(int *old_fd);
#endif

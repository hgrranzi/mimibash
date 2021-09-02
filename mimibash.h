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
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>

# include "Libft/libft.h"

# define PROMPT "✅ mimibash 💬 "
# define ERR_CMD "command not found"
# define ERR_SYNTAX "syntax error"
# define ERR_UNSET "not a valid identifier"
# define ERR_EXIT_NO_DIGITS "numeric argument required"
# define ERR_EXIT_MANY_ARGS "too many arguments"
# define ERR_HOME "HOME not set"
# define ERR_SHLVL "shell level too high, resetting to 1"
# define ENV_PREFIX "declare -x"
# define IN 0
# define OUT 1
# define CMD_PATH 0
# define CURRENT_DIR "."
# define IS_CHILD 0

typedef enum e_builtin
{
	NO_BUILTIN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	ERROR_BUILTIN
}			t_builtin;

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
	int		exit_status;
}				t_redir;

/* mimibash.c */

void	mimibash_loop(int new_in, int (**builtins)(int *, char **, char ***), char ***envp);
char	*read_cmd(int new_in);
void	error_and_exit(char *reason, char *error_message, int end);

/* handle_signal.c */

int		handle_signal(void);
void	handle_sigint(int sig_number);
int		handle_signal_pipe(void);
void	handle_sig_pipe(int sig_number);

/* builtins.c */

int		exec_cd(int *fd, char **arg, char ***envp);
char	*check_dir(char *arg, char **envp);
char	*take_var(char **envp, char *var);
int		update_wd_var(char ***envp, char *new_wd, int i);
int		exec_pwd(int *fd, char **arg, char ***envp);

/* builtins_again.c */

int		exec_echo(int *fd, char **arg, char ***envp);
int		exec_export(int *fd, char **arg, char ***envp);
int		exec_unset(int *fd, char **arg, char ***envp);
int		exec_env(int *fd, char **arg, char ***envp);
int		exec_exit(int *fd, char **arg, char ***envp);

/* print_sorted_env.c */

int		print_sorted_env(int *fd, char **envp);
char	**add_quotes(char **arr, int arr_len);
char	*quote_str(char *str);
void	sort_env(char **arr, int arr_len);
char	**take_variables(char **arr);

/* export_unset_utils.c */

int		find_variable(char *var, int var_len, char *arg, char **envp);
int		find_place(char *arg, char **envp);
int		new_place(char *arg, char ***envp);
void	remove_variable(char *arg, char **envp);
int		exec_error(int *fd, char **arg, char ***envp);

/* init.c */

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
int		exec_builtins(t_data *head_data, int (**builtins)(int *, char **, char ***), char ***envp);
int		exec_pipes(t_data **head_data, int (**builtins)(int *, char **, char ***), char ***envp);
int		create_processes(t_data **head_data, t_info *info, int (**builtins)(int *, char **, char ***), char ***envp);
void	exec_exec(t_data *head_data_p, int (**builtins)(int *, char **, char ***), char ***envp);

/* exec_cmd_utils.c */

int		count_cmd(t_data **head_data);
void	distribute_fd(t_data **head_data, int **pipe_fd);
void	close_unused_pipe_fd(int **pipe_fd, int i, int cmd_count);
void	duplicate_fd(int *fd);
int		is_error(char **args);

/* exec_cmd_finish.c */

int		wait_and_close(pid_t *pid, int cmd_count);
void	close_pipes(int **pipe_fd, int cmd_count);

/* utils.c */

int		only_digits(char *str);

/* update_underscore.c */

void	update_underscore(t_data **head_data, char ***envp);
char	*take_last_arg(t_data **head_data);

/* wildcard.c */

t_list	*check_wildcard(char *str);
t_list	*find_equals(char *str, DIR *opened_wd);
int		are_equal(char *s1, char *s2);

/* parser.c */

void	parser(char **input, char **envp, t_data **data, int exit_status);
void	fill_struct(t_data *data);
void	check_echo_n(t_data *data);
void	check_empty(char **str);
int		ft_key(char c);

/* parse_redir.c */

char	*parse_redir(char **str, int *fd, char **envp, int exit_status);
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

/* check_builtins.c */

void	check_builtins(t_data *data, int exit_status);
void	check_unset(t_data *data);
void	check_exit(char ***args, int exit_status);
void	check_export(t_data *data);

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

char	**add_n(char **args);

/* shielding.c */

char	**shielding(char **str, char **env, int exit_status);
char	*parse_exitcode(char *str, int *i, int exit_code);
char	*parse_dollar(char *str, int *i, char **env);
char	*unpack(char **str, char **env, char *str2, int *j);
void	spec_free(char **str1, char **str2, char **str3);

/* shielding_utils.c */

char	*parse_double_quote(char *str, int *i, char **env, int exit_status);
char	*parse_single_quote(char *str, int *i);
char	*getstr(char *str, int i, int j);
char	*parse_slash(char *str, int *i);

/* heredoc.c */

void	heredoc(t_redir *red);
void	make_heredoc(t_redir *red, int j, int n);
void	parse_heredoc(t_redir *red);
void	fill_heredoc(t_redir *red, char *delimiter);
int		create_heredoc(int *old_fd);

/* parse_star.c */

char	**parse_star(char ***str);
char	**masjoin(char **str1, char *str2);
char	**new_star_massive(char **massive, int i, char **old_tmp);
int		massive_size(char **mas);
int		check_quotes(char *str);

/* check_builtins_utils.c */

void	print_export_error(t_data *data, int i);
void	print_unset_error(t_data *data, int i);

void	check_echo(t_data *data);
void	fill_massive(t_data *data, int i);
int		check_another_symbol(char *str);
void	check_fd(int *fd, int j, char **bzero);

char	*getstrquote(char *str, int i, int j);
#endif

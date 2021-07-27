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
# define ERR_CMD "command not found"
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
	EXIT
}			t_builtin;

typedef struct s_data
{
	int				builtin;
	char			**args;
	int				fd[2];
	struct s_data	*next;
}				t_data;

/* handle_signal */

int		handle_signal(void);

/* init.c */

t_data	*init_data(void);
void	init_builtin_functions(int (**builtin_functions)(int *, char **));
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

int		exec_cmd(t_data **head_data, int (**cmd_functions)(int *, char **), char **envp);
int		exec_pipes(t_data **head_data, int (**builtin_functions)(int *, char **), char **envp);
int		create_processes(t_data **head_data, int cmd_count, pid_t *pid, int **pipe_fd);

/* exec_cmd_utils.c */

int		count_cmd(t_data **head_data);
void	distribute_fd(t_data **head_data, int **pipe_fd);
void	close_unused_pipe_fd(int **pipe_fd, int i, int cmd_count);
void	duplicate_fd(int *fd);
void	wait_and_close(pid_t *pid, int **pipe_fd, int cmd_count);

/* error.c */

void	error_and_exit(char *reason, char *error_message, int end);
int		cmd_error(char *cmd, int error_code);
void	system_error(int error_code);

#endif

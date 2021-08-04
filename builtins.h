#ifndef BUILTINS_H
# define BUILTINS_H

# define ENV_PREFIX "declare -x"
# define ERR_HOME "HOME not set"

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

/* builtins.c */

int		exec_echo(int *fd, char **arg, char ***envp);
int		exec_cd(int *fd, char **arg, char ***envp);
char	*check_dir(char *arg, char **envp);
char	*take_var(char **envp, char *var);
int		update_wd_var(char ***envp, char *new_wd, int i);
int		exec_pwd(int *fd, char **arg, char ***envp);
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

#endif

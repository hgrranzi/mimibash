#ifndef BUILTINS_H
# define BUILTINS_H

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

int		exec_echo(int *fd, char **arg, char ***envp);
int		exec_cd(int *fd, char **arg, char ***envp);
int		exec_pwd(int *fd, char **arg, char ***envp);
int		exec_export(int *fd, char **arg, char ***envp);
int		find_variable(char *var, int var_len, char *arg, char **envp);
int		find_place(char *arg, char **envp);
int		new_place(char *arg, char ***envp);
int		exec_unset(int *fd, char **arg, char ***envp);
void	remove_variable(char *arg, char **envp);
int		exec_env(int *fd, char **arg, char ***envp);
int		exec_exit(int *fd, char **arg, char ***envp);

#endif

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

int		exec_echo(int *fd, char **arg);
int		exec_cd(int *fd, char **arg);
int		exec_pwd(int *fd, char **arg);
int		exec_export(int *fd, char **arg);
int		exec_unset(int *fd, char **arg);
int		exec_env(int *fd, char **arg);
int		exec_exit(int *fd, char **arg);

#endif

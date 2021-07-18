#ifndef BUILTINS_H
# define BUILTINS_H

int		cmd_error(char *cmd, int error_code);
void	init_builtin_functions(int (**cmd_functions)(int, char **));

int		exec_echo(int fd, char **arg);
int		exec_cd(int fd, char **arg);
int		exec_pwd(int fd);
int		exec_export(int fd, char **arg);
int		exec_unset(int fd, char **arg);
int		exec_env(int fd, char **arg);
int		exec_exit(int fd, char **arg);

#endif

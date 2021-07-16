#ifndef BUILTINS_H
# define BUILTINS_H

int	cmd_error(char *cmd, int error_code);

int	exec_echo(int fd, char *arg);
int	exec_pwd(int fd);

#endif

#include "mimibash.h"

int	exec_echo(int *fd, char **arg, char ***envp)
{
	char	***no_need;
	int		i;

	no_need = envp;
	i = 1;
	while (arg && arg[i])
	{
		write(fd[OUT], arg[i], ft_strlen(arg[i]));
		if (i && arg[i + 1] && arg[i + 1][0] != '\n')
			write(fd[OUT], " ", 1);
		i++;
	}
	return (0);
}

int	exec_export(int *fd, char **arg, char ***envp)
{
	int		i;
	int		var_len;
	char	*var;
	int		exit_code;

	i = 1;
	exit_code = 0;
	if (!arg[i])
		return (print_sorted_env(fd, *envp));
	while (arg[i])
	{
		if (!arg[i][0])
			exit_code = 1;
		else if (ft_strchr(arg[i], '='))
		{
			var_len = index_char(arg[i], '=');
			var = ft_strndup(arg[i], var_len);
			if (!var)
				error_and_exit(NULL, NULL, 1);
			find_variable(var, var_len, arg[i], *envp) || find_place(arg[i], *envp) || new_place(arg[i], envp);
			free(var);
		}
		i++;
	}
	return (exit_code);
}

int	exec_unset(int *fd, char **arg, char ***envp)
{
	int	*no_need;
	int	i;
	int	exit_code;

	no_need = fd;
	i = 1;
	exit_code = 0;
	while (arg[i])
	{
		if (!arg[i][0])
			exit_code = 1;
		else
			remove_variable(arg[i], *envp);
		i++;
	}
	return (exit_code);
}

int	exec_env(int *fd, char **arg, char ***envp)
{
	char	**no_need;
	int		i;

	no_need = arg;
	i = 0;
	while ((*envp)[i])
	{
		if ((*envp)[i][0])
		{
			write(fd[OUT], (*envp)[i], ft_strlen((*envp)[i]));
			write(fd[OUT], "\n", 1);
		}
		i++;
	}
	return (0);
}

int	exec_exit(int *fd, char **arg, char ***envp)
{
	char	***no_need;
	long	exit_code;

	no_need = envp;
	exit_code = 0;
	if (fd[IN] == STDIN_FILENO)
		write(STDERR_FILENO, "exit\n", 6);
	if (only_digits(arg[1]))
	{
		if (arg[2])
		{
			error_and_exit("exit", ERR_EXIT_MANY_ARGS, 0);
			return (1);
		}
		exit_code = ft_atoi(arg[1]);
	}
	else
	{
		error_and_exit("exit", ERR_EXIT_NO_DIGITS, 0);
		exit_code = 255;
	}
	close(fd[IN]);
	close(fd[OUT]);
	exit((exit_code + 256) % 256);
}

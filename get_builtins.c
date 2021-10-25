#include "mimibash.h"

char	*make_same(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 65 && str[i] <= 90)
			str[i] += 32;
		i++;
	}
	return (str);
}

void	get_builtins(char **str, int *built)
{
	int		n;
	char	*tmp;

	*built = NO_BUILTIN;
	tmp = ft_strdup(*str);
	tmp = make_same(tmp);
	n = ft_strlen(*str);
	if (!ft_strncmp(tmp, "echo", n + 1))
		*built = ECHO;
	if (!ft_strncmp(tmp, "cd", n + 1))
		*built = CD;
	if (!ft_strncmp(tmp, "pwd", n + 1))
		*built = PWD;
	if (!ft_strncmp(tmp, "export", n + 1))
		*built = EXPORT;
	if (!ft_strncmp(tmp, "unset", n + 1))
		*built = UNSET;
	if (!ft_strncmp(tmp, "env", n + 1))
		*built = ENV;
	if (!ft_strncmp(tmp, "exit", n + 1))
		*built = EXIT;
	if (!ft_strncmp(tmp, "258", n + 1))
		*built = ERROR_BUILTIN;
	free(tmp);
}

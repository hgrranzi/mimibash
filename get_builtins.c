#include "mimibash.h"
char *make_same(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >=65 && str[i] <= 90)
			str[i]+=32;
		i++;
	}
	return (str);
}

void get_builtins(char **str, int *built)
{
	int n;

	*built = 0;
	*str = make_same(*str);
	n = ft_strlen(*str);
	if (!ft_strncmp(*str, "echo", n + 1))
		*built = 1;
	if (!ft_strncmp(*str, "cd", n + 1))
		*built = 2;
	if (!ft_strncmp(*str, "pwd", n + 1))
		*built = 3;
	if (!ft_strncmp(*str, "export", n + 1))
		*built = 4;
	if (!ft_strncmp(*str, "unset", n + 1))
		*built = 5;
	if (!ft_strncmp(*str, "env", n + 1))
		*built = 6;
	if (!ft_strncmp(*str, "exit", n + 1))
		*built = 7;
	// free (str);
	if (*built > 0)
	{
		free(*str);
		*str = ft_strdup("\0");
	}
	
	// parse_builtins(str[0], built);
}

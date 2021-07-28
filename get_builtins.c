#include "minishell.h"
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
// void parse_builtins(char *str, int b)
// {
// 	int i;

// 	i = 0;
// 	if (b == 0)
// 	{
// 		if (str[0] == '/')
			
// 	}
// 	while (str[i] != '\0')
// }
void get_builtins(char *str, int *built)
{
	int n;

	*built = 0;
	str = make_same(str);
	n = ft_strlen(str);
	if (!ft_strncmp(str, "echo", n))
		*built = 1;
	if (!ft_strncmp(str, "cd", n))
		*built = 2;
	if (!ft_strncmp(str, "pwd", n))
		*built = 3;
	if (!ft_strncmp(str, "export", n))
		*built = 4;
	if (!ft_strncmp(str, "unset", n))
		*built = 5;
	if (!ft_strncmp(str, "env", n))
		*built = 6;
	if (!ft_strncmp(str, "exit", n))
		*built = 7;
	// parse_builtins(str[0], built);
}

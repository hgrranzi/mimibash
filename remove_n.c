#include "mimibash.h"
char **remove_n(char **args, int built)
{
	int i;
	char **tmp;

	i = 0;
	while(args[i] != NULL)
		i++;
	tmp = malloc(sizeof(char *) * (i));
	tmp[0] = args[0];
	i = 2;
	while (args[i] != NULL)
	{
		tmp[i - 1] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	tmp[i-1] = NULL;
	return (tmp);
}
char **add_n(char **args, int builtin)
{
	int i;
	int n;
	char **tmp;

	i = 0;
	while (args[i] != NULL)
		i++;
	n = i;
	i = 0;
	tmp = malloc((n + 2)*sizeof(char *));
	while (i < n)
	{
		tmp[i] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	tmp[i++] = ft_strdup("\n");
	tmp[i] = NULL;
	return (tmp);
}
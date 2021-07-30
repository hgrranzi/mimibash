#include "mimibash.h"
char **remove_n(char **args, int built)
{
	int i;
	char **tmp;

	i = 0;
	while(args[i] != NULL)
		i++;
	tmp = malloc(sizeof(char *) * i - 2);
	tmp[0] = args[0];
	i = 2;
	while (args[i + 1] != NULL)
	{
		tmp[i - 1] = ft_strdup(args[i]);
		free(args[i]);
		i++;
	}
	tmp[i] = NULL;

	return (tmp);
}
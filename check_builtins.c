#include "mimibash.h"
char **check_export(char **args)
{
	int i;
	int j;

	i = 0;
	while (args[i] != NULL)
	{
		j = 0;
		while (args[i][j] != '\0')
		{
			if (!ft_key(args[i][j]) && args[i][j]!='=')
			{
				args[i] = ft_strdup("\0");
				j = -1;
			}
			if (args[i][j]=='=')
				break;
			j++;
		}
		i++;	
	}
	return (args);
}

char **check_builtins(t_data *data)
{
	
	if (data->builtin == 4)
		data->args = check_export(data->args);

	return(data->args);
}
// #include "mimibash.h"
// char **check_export(char **args)
// {
// 	int i;
// 	int j;
// 	char **tmp;

// 	i = 0;
// 	while(args[i] != NULL)
// 		i++;
// 	tmp = malloc(sizeof(char *) * (i + 1));
// 	i = 0;
// 	while (args[i] != NULL)
// 	{
// 		j = 0;
// 		while (args[i][j] != '\0')
// 		{
// 			if (!ft_key(args[i][j]))
// 			{
// 				tmp[i] = ft_strdup("");
// 				i++;
// 				j = 0;
// 			}
// 			j++;
// 		}
			
// 	}
// }
// char **check_builtins(t_data *data)
// {
// 	if (data->builtin == 4)
// 		data->args = check_export(data->args);
// }
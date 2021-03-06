#include "mimibash.h"

int	check_quotes(char *str)
{
	int	j;

	j = 0;
	while (str[j] != '\0')
	{
		if (str[j] == '\"' || str[j] == '\''
			|| str[j] == '\\' || str[j] == '$')
			return (0);
		j++;
	}
	return (1);
}

void	fill_star_massive(char ***tmp, char **old_tmp, t_list *data)
{
	int	i;

	i = 0;
	while (old_tmp && old_tmp[i])
	{
		(*tmp)[i] = ft_strdup(old_tmp[i]);
		i++;
	}
	while (data != NULL)
	{
		(*tmp)[i] = ft_strdup(data->content);
		data = data->next;
		i++;
	}
	(*tmp)[i] = NULL;
}

char	**new_star_massive(char **massive, int i, char **old_tmp)
{
	char	**tmp;
	t_list	*data;
	t_list	*ptr;

	data = check_wildcard(massive[i]);
	if (data == NULL)
		return (masjoin(old_tmp, massive[i]));
	ptr = data;
	tmp = malloc(sizeof(char *) * (ft_lstsize(data)
				+ massive_size(old_tmp) + 1));
	fill_star_massive(&tmp, old_tmp, data);
	free_arr(old_tmp);
	old_tmp = NULL;
	ft_lstclear(&ptr, free);
	return (tmp);
}

char	**masjoin(char **str1, char *str2)
{
	char	**tmp;
	int		j;

	j = 0;
	tmp = malloc(sizeof(char *) * (massive_size(str1) + 2));
	while (str1 && str1[j])
	{
		tmp[j] = ft_strdup(str1[j]);
		j++;
	}
	tmp[j] = ft_strdup(str2);
	j++;
	tmp[j] = NULL;
	free_arr(str1);
	str1 = NULL;
	return (tmp);
}

char	**parse_star(char ***str)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = NULL;
	while ((*str)[i] != NULL)
	{
		if (check_quotes((*str)[i]))
		{
			if (ft_strchr((*str)[i], '*'))
				tmp = new_star_massive(*str, i, tmp);
			else
				tmp = masjoin(tmp, (*str)[i]);
		}
		else
			tmp = masjoin(tmp, (*str)[i]);
		i++;
	}
	if (tmp)
	{
		free_arr(*str);
		(*str) = NULL;
		return (tmp);
	}
	return (*str);
}

#include "mimibash.h"

int	index_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

char	*aka_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	new_str = malloc((strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_str[i] = s2[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

int	words_count(const char *s, char delimiter)
{
	int	res;
	int	i;

	res = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == delimiter)
			i++;
		if (s[i] != '\0')
			res++;
		while (s[i] && s[i] != delimiter)
			i++;
	}
	return (res);
}

char	*trim_line(char *s, char c)
{
	char	*trimmed_str;
	int		start_trim;
	int		finish_trim;

	if (s == NULL)
		return (NULL);
	start_trim = 0;
	finish_trim = ft_strlen(s) - 1;
	while (start_trim < finish_trim && c == s[start_trim])
		start_trim++;
	while (finish_trim > start_trim && c == s[finish_trim])
	{
		s[finish_trim] = '\0';
		finish_trim--;
	}
	trimmed_str = ft_strdup(&s[start_trim]);
	return (trimmed_str);
}

char	**split_line(char *s, char c)
{
	char	*new_str;
	int		arr_len;
	char	**arr;
	int		i;
	int		start;

	i = 0;
	start = 0;
	arr = NULL;
	new_str = trim_line(s, c);
	if (!new_str)
		return (NULL);
	arr_len = words_count(new_str, c);
	arr = calloc(arr_len + 1, sizeof(char *));
	while (arr && i < arr_len)
	{
		arr[i] = ft_strndup(&new_str[start], index_char(&new_str[start], c));
		if (!arr)
			return (free_arr(arr));
		start = start + ft_strlen(arr[i]);
		while (new_str[start] == c)
			start++;
		i++;
	}
	free(new_str);
	new_str = NULL;
	return (arr);
}

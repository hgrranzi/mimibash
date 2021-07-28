/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <tmiranda@srudent.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 17:05:57 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 18:52:31 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mimibash.h"

static size_t	ft_countword(char const *s, char c)
{
	int			i;
	int			k;
	int			n;
	int			count;

	i = 0;
	k = 0;
	n = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' && (n%2) == 0)
		{
			k++;
			i++;
		}
		if (s[i] == '\'' && (k%2) == 0)
		{
			n++;
			i++;
		}
		if((k%2) == 0 && (n%2) == 0)
		{
			if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
				count++;
		}
		i++;
	}
	count += k / 2;
	return (count);
}

static size_t	ft_wrdlen(char const *s, char c)
{
	int			i;
	int			k;
	int			n;

	i = 0;
	k = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\"' && (n%2) == 0)
		{
			k++;
			i++;
		}
		if (s[i] == '\'' && (k%2) == 0)
		{
			n++;
			i++;
		}
		if((k%2) == 0 && (n%2) == 0)
		{
			while(s[i] != c && s[i] != '\0')
				i++;
			return (i);
		}
		else
		{
			while(s[i] != '\"' && s[i] != '\0')
				i++;
			return (i + 1);
		}
		i++;
	}
	return (i);
}

static char	**ft_free(char **s)
{
	int	i;

	i = 0;
	while (*s)
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

char	**new_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**str;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	str = (char **)ft_calloc((ft_countword(s, c) + 1), sizeof(char *));
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			str[j++] = ft_substr((s + i), 0, ft_wrdlen(s + i, c));
			if (!str)
				return (ft_free(str));
			i += ft_wrdlen(s + i, c);
		}
	}
	str[j] = NULL;
	return (str);
}

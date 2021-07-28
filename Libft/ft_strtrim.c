/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <tmiranda@srudent.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:59:56 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 18:58:27 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static int	val_ret(int n, int i)
{
	if (n > i)
		return (n - i);
	else
		return (i - n);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	count;
	size_t	n;
	char	*str;

	i = 0;
	count = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]) != 0)
		i++;
	n = ft_strlen(s1);
	if (i == n)
		return (str = ft_substr("", 0, 1));
	while (ft_strchr(set, s1[n]) != 0)
		n--;
	count = val_ret(n, i);
	str = ft_substr(s1, i, count + 1);
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <tmiranda@srudent.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:46:43 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 19:03:37 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
static size_t	val_ret(int n, unsigned int start, size_t len)
{
	if (n - start < len)
		return (n - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sb;
	size_t	i;
	size_t	mlen;

	i = 0;
	if (s == NULL)
		return (NULL);
	mlen = val_ret(ft_strlen(s), start, len);
	sb = malloc(mlen + 1);
	if (sb == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		sb[i] = '\0';
		return (sb);
	}
	while (i < len && s[start] != '\0')
	{
		sb[i] = s[start];
		i++;
		start++;
	}
	sb[i] = '\0';
	return (sb);
}

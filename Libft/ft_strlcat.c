/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <tmiranda@srudent.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:46:51 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 18:53:45 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	lendst;
	size_t	len;
	size_t	j;

	i = 0;
	lendst = ft_strlen(dst);
	j = lendst;
	if (lendst > dstsize)
		lendst = dstsize;
	len = lendst + ft_strlen(src);
	if (dstsize > lendst)
	{
		while (j < dstsize - 1 && src[i] != '\0')
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
	}
	return (len);
}

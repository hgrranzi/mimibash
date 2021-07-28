/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <tmiranda@srudent.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:30:32 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 18:43:08 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst2;
	unsigned char	*src2;

	if (dst == NULL && src == NULL)
		return (NULL);
	src2 = (unsigned char *)src;
	dst2 = (unsigned char *)dst;
	i = 0;
	if (dst2 > src2)
	{
		while (len--)
		{
			dst2[len] = src2[len];
		}
	}
	else if (dst2 < src2)
	{
		while (i < len)
		{
			dst2[i] = src2[i];
			i++;
		}
	}
	return (dst);
}

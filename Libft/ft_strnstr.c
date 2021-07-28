/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <tmiranda@srudent.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 15:57:54 by tmiranda          #+#    #+#             */
/*   Updated: 2021/04/07 18:54:49 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	lenndl;
	char	*hay;

	i = 0;
	hay = (char *)haystack;
	if (needle == NULL || haystack == NULL)
		return (NULL);
	lenndl = ft_strlen(needle);
	if (len == 0 && lenndl != 0)
		return (NULL);
	if (lenndl == 0)
		return (hay);
	while (hay[i] != '\0' && i <= len - lenndl)
	{
		if (hay[i] == needle[0])
		{
			if (ft_strncmp(hay + i, needle, lenndl) == 0)
				return (hay + i);
		}
		i++;
	}
	return (NULL);
}

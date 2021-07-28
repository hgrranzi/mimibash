/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmiranda <tmiranda@srudent.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 16:43:28 by tmiranda          #+#    #+#             */
/*   Updated: 2020/11/17 17:33:10 by tmiranda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s;
	size_t	n;

	i = 0;
	n = ft_strlen(s1);
	s = malloc(n + 1);
	if (s == NULL)
		return (NULL);
	while (i < n)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

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

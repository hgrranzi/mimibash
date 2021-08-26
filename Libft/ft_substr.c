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

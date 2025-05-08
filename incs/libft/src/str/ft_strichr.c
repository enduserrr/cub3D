#include "../../incs/libft.h"

ssize_t	ft_strichr(const char *s, int c)
{
	ssize_t	i;

	i = 0;
	while (s[i])
		if (s[i++] == (char)c)
			return (i);
	if ((char)c == '\0')
		return (i);
	return (-1);
}

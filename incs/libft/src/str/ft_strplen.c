#include "../../incs/libft.h"

/**
 * @brief	Checking the pointer before iterating through the string
 */
size_t	ft_strplen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

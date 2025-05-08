#include "../../incs/libft.h"

/**
 * @brief	Search for the first occurrence of 'c' (as an unsigned char)
 * 			in the first 'n' num of bytes of the object pointed to by s.
 * 			If the character is found, returns a pointer to the matching byte.
 * 			Otherwise, returns a null pointer.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (((unsigned char *)s) + i);
		i++;
	}
	return (0);
}

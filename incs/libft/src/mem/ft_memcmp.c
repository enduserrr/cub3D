#include "../../incs/libft.h"

/**
 * @brief	Compare the first 'n' bytes of the memory areas pointed to
 * 			by 's1' and 's2'. Returns an int based on the first differing byte
 * 			(if there's one) by the amount the differ in position (or don't)
 * 			in the ASCII table.
*/
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

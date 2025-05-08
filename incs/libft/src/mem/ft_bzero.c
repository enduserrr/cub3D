#include "../../incs/libft.h"

/**
 * @brief	Set's the specified block of memory to zero.
*/
void	ft_bzero(void *s, size_t n)
{
	while (n--)
		*(char *)s++ = 0;
}

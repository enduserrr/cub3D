#include "../../incs/libft.h"

/**
 * @brief	Fill the first 'len'number of bytes of the memory area 
 *			pointed to by 'b' with the constant byte 'c'.
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i++] = c;
	}
	return (b);
}

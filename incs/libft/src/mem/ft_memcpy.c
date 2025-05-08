#include "../../incs/libft.h"

/**
 * @brief	Copy the memory starting from src pointer for 'n' bytes
 * 			to the destination pointed by 'dst'.
*/
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dst);
}

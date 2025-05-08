#include "../../incs/libft.h"

/**
 * @brief	Copy 'len' bytes from the memory area pointed by 'src'
 * 			to the memory area pointed by 'dst', while handling overlapping
 * 			memory regions correctly.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d2;
	unsigned char	*s2;

	d2 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	if (!dst && !src)
		return (0);
	if (src < dst)
	{
		s2 = s2 + len - 1;
		d2 = d2 + len - 1;
		while (len--)
			*d2-- = *s2--;
	}
	else if (src >= dst)
	{
		while (len--)
			*d2++ = *s2++;
	}
	return (dst);
}

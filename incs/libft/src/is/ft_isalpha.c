#include "../../incs/libft.h"

/**
 * @brief	return non zero value if true and 0 if not.
 */
int	ft_isalpha(int c)
{
	return ((c > 64 && c < 91) || (c > 96 && c <= 122));
}

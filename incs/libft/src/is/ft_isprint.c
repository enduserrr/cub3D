#include "../../incs/libft.h"

/**
 * @brief	return non zero value if true and 0 if not.
 */
int	ft_isprint(int c)
{
	return (c > 31 && c < 127);
}

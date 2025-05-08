#include "../../incs/libft.h"

/**
 * @brief	return non zero value if true and 0 if not.
 */
int	ft_isspace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

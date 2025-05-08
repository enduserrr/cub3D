#include "../../incs/libft.h"

/**
 * @brief	return non zero value if true and 0 if not.
 */
int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

#include "../../incs/libft.h"

/**
 * @brief	Return TRUE if character given is one the six white space chars.
 * 			Using lookup table to speed up the process as now the function
 * 			directly accesses the value at the index corresponding to
 * 			the char code of c in the array.
*/

int	ft_lookup_space(char c)
{
	static unsigned char	space_table[255] = {0};

	space_table[32] = 1;
	space_table[9] = 1;
	space_table[10] = 1;
	space_table[11] = 1;
	space_table[12] = 1;
	space_table[13] = 1;
	return (space_table[(unsigned char)c]);
}

#include "../../incs/libft.h"

/**
 * @brief   Modify to add string 'c' into string 's' starting from 'start'.
 *          Returns (void *)0 upon succes and (void *)1 upon failure.
 *
 *          Copy the part of 'ret' before 'start'.
 *          Insert 'len' nb of chars from 'insert'.
 *          Copy the re of ret after 'start'.
 *          Copy the modified str back to 'ret'.
 *          Free temp.
 */
void	*ft_strinsrt(char **ret, const char *insert, size_t start, size_t len)
{
	size_t	new_len;
	size_t	ret_len;
	char	*temp;

	if (!ret || !*ret)
		return ((void *)1);
	if (!insert)
		insert = "";
	ret_len = ft_strlen(*ret);
	if (start > ret_len)
		return ((void *)1);
	new_len = ret_len - len + ft_strlen(insert);
	temp = ft_calloc(new_len + 1, sizeof(char));
	if (!temp)
		return ((void *)1);
	ft_memcpy(temp, *ret, start);
	ft_memcpy(&temp[start], insert, ft_strlen(insert));
	ft_memcpy(&temp[start + ft_strlen(insert)], &(*ret)[start + len], ret_len
		- start - len);
	free(*ret);
	*ret = temp;
	return (NULL);
}

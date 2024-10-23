/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:02:02 by asalo             #+#    #+#             */
/*   Updated: 2024/10/18 08:58:30 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

/**
 * @brief	Joins two strings; s1 & s2, into NULL terminated new string
 *			with sufficient mem allocated. Handles empty strings.
*/
char *ft_strjoin_mod(char const *s1, char const *s2)
{
	char	*new;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	new = NULL;
	if (s1 != NULL)
		len1 = ft_strlen(s1);
	if (s2 != NULL)
		len2 = ft_strlen(s2);
    new = malloc(len1 + len2 + 1);
    if (!new)
        return (NULL);
    if (s1)
        ft_strcpy(new, s1);
    if (s2)
        ft_strcpy(new + len1, s2);
    return (new);
}

void	put_arr(char **arr)
{
	int	k;

	k = 0;
	while (arr[k])
	{
		while (*arr[k])
			write(1, arr[k]++, 1);
		write(1, "\n", 1);
		k++;
	}
	return ;
}

int is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	is_valid(char c)
{
    if (is_player(c) || c == ' ' || c == '0' || c == '1')
        return (1);
    return (0);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

// char	*read_fd(int fd)
// {
// 	int		read_value;
// 	char	*new;
// 	char	*tmp;
// 	char	*buffer[4096];

// 	new = NULL;
// 	read_value = 1;
// 	while ((read_value = read(fd, buffer, 4095)) > 0)
// 	{
// 		buffer[read_value] = '\0';
// 		tmp = new;
// 		free(tmp);
// 	}
// 	if (read_value == -1)
// 	{
// 		if (new != NULL)
// 			free(new);
// 		return (NULL);
// 	}
// 	return (new);
// }

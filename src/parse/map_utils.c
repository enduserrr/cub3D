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

#include "../../incs/cub3D.h"

/**
 * @brief	Valid player position & starting orientation characters.
 */
int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	atoi_mod(const char *s)
{
	unsigned long long	res;

	res = 0;
	if (!*s)
		return (-1);
	while (*s == ' ')
		s++;
	if (*s < '0' || *s > '9')
		return (-1);
	while (*s)
	{
		if (*s >= '0' && *s <= '9')
			res = res * 10 + *s - '0';
		if (*s < '0' || *s > '9')
			return (-1);
		s++;
	}
	if (res > 255 || res < 0)
		return (-1);
	return (res);
}

/**
 * @brief	Like strjoin with handling for empty strings.
 *			Accounts for 0 length.
 */
char	*strjoin_modi(char *s1, char *s2)
{
	char	*result;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strplen(s1);
	len2 = ft_strplen(s2);
	if ((len1 + len2) < 1)
		result = ft_calloc(len1 + len2, sizeof(char *));
	result = ft_calloc(len1 + len2 + 1, sizeof(char *));
	if (!result)
	{
		free(s1);
		return ((void *)1);
	}
	ft_memcpy(result, s1, len1);
	free(s1);
	ft_memcpy(result + len1, s2, len2 + 1);
	return (result);
}

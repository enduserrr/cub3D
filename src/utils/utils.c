/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:02:02 by asalo             #+#    #+#             */
/*   Updated: 2024/11/24 10:57:44 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

int	atoi_mod(const char *s)
{
	int	res;

	res = 0;
	if (!*s || *s == '\0')
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

void	strlcpy_modi(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}

void	write_err(char *s)
{
	write(2, RB, ft_strlen(RB));
	write(2, "Error:\n", ft_strlen("Error:\n"));
	write(2, W, ft_strlen(W));
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	write(2, RES, ft_strlen(RES));
}

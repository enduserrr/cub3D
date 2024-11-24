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

void	write_err(char *s)
{
	write(2, RB, ft_strlen(RB));
	write(2, "Error: ", ft_strlen("Error: "));
	write(2, W, ft_strlen(W));
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	write(2, RES, ft_strlen(RES));
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr == NULL || *arr == NULL)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_map(t_game *game)
{
	size_t	i;

	i = 0;
	if (!game || !game->data || !game->data->map)
		return ;
	while (game->data->map[i] != NULL)
	{
		free(game->data->map[i]);
		i++;
	}
	free(game->data->map);
	game->data->map = NULL;
}

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

int is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

char	*strjoin_mod(char *s1, char *s2, int *line_end)
{
	char	*result;
	size_t	len1;
	size_t	len2;

    (void)line_end;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strplen(s1);
	len2 = ft_strplen(s2);
    if ((len1 + len2) < 1)/*Changed*/
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
	// if (len1 + len2 > 0 && *(result + len1 + len2 - 1) == '\n')
	// 	*line_end = 0;
	return (result);
}

void set_player_direction(t_game *game, double pax, double pay, double plane_x, double plane_y)
{
    game->player->pax = pax;
    game->player->pay = pay;
    game->player->plane_x = plane_x;
    game->player->plane_y = plane_y;
}

void set_player(t_game *game, char c, size_t x, size_t y)
{
    game->player->ppx = (double)x + 0.3;
    game->player->ppy = (double)y + 0.3;

    if (c == 'N')
        set_player_direction(game, 0.0, -1.0, FOV, 0.0);
    else if (c == 'S')
        set_player_direction(game, 0.0, 1.0, -FOV, 0.0);
    else if (c == 'W')
        set_player_direction(game, -1.0, 0.0, 0.0, -FOV);
    else if (c == 'E')
        set_player_direction(game, 1.0, 0.0, 0.0, FOV);
}

int validate_file(char *name)
{
    int fd;

    if (!name || ft_strlen(name) < 4 ||
        ft_strcmp(name + (ft_strlen(name) - 4), ".cub"))
        return (write_err("invalid map"), -1);
    fd = open(name, O_RDONLY);
    if (fd < 0)
	{
		close(fd);
		return (write_err("unable to open the map file"), -1);
	}
	close(fd);
    return (fd);
}

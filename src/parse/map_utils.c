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

char	*gnl_strjoin_mod(char *s1, char *s2, int *line_end)
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
// void player_direction(t_game *game, double pax, double pay, double px, double py)
// {
// 	game->player->pax = pax;
//     game->player->pay = pay;
//     game->player->plane_x = px;
//     game->player->plane_y = py;	
// }

// void set_player(t_game *game, char c, size_t x, size_t y)
// {
//     game->player->ppx = (double)x + 0.3;
//     game->player->ppy = (double)y + 0.3;
//     if (c == 'N') 
// 		player_direction(game, 0.0, -1.0, FOV, 0.0);
//     else if (c == 'S') 
//         player_direction(game, 0.0, 1.0, -FOV, 0.0);
//     else if (c == 'W') 
//         player_direction(game, -1.0, 0.0, 0.0, -FOV);
//     else if (c == 'E') 
//         player_direction(game, 1.0, 0.0, 0.0, FOV);
// }

void set_player(t_game *game, char c, size_t x, size_t y)
{
    game->player->ppx = (double)x + 0.3;
    game->player->ppy = (double)y + 0.3;

    if (c == 'N')  // Facing North
    {
        game->player->pax = 0.0;
        game->player->pay = -1.0;
        game->player->plane_x = FOV;
        game->player->plane_y = 0.0;
    }
    else if (c == 'S')  // Facing South
    {
        game->player->pax = 0.0;
        game->player->pay = 1.0;
        game->player->plane_x = -FOV;
        game->player->plane_y = 0.0;
    }
    else if (c == 'W')  // Facing West
    {
        game->player->pax = -1.0;
        game->player->pay = 0.0;
        game->player->plane_x = 0.0;
        game->player->plane_y = -FOV;
    }
    else if (c == 'E')  // Facing East
    {
        game->player->pax = 1.0;
        game->player->pay = 0.0;
        game->player->plane_x = 0.0;
        game->player->plane_y = FOV;
    }
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

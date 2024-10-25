/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:59:24 by asalo             #+#    #+#             */
/*   Updated: 2024/10/25 10:25:18 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

void    clean_mem(void *ptr, t_type type)
{
    // size_t  i;
    t_map   *map;
    t_txtr  *txtr;
    t_game  *game;

    if (!ptr)
        return ;
    if (type == MAP)
    {
        map = (t_map *)ptr;
        free_arr(map->temp_map);
        map->temp_map = NULL;
    }
    else if (type == TXTR)
    {
        txtr = (t_txtr *)ptr;
        free_arr(txtr->info);
        txtr->info = NULL;
    }
    else if (type == GAME)
    {
        game = (t_game *)ptr;
        free_arr(game->map);
        game->map = NULL;
    }
}


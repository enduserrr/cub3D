/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_side.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:49:00 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/30 20:49:02 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

// static void corner_case(t_game *game, int i)
// {
//     game->ray[i].corner = true;
//     {
//         game->ray[i].hs = game->ray[i - 1].hs;
//     }   
// }

// static void horizontal_hit(t_game *game, int i)
// {
//     if (game->player->pa > 0 && game->player->pa < PI)
//     {
//         if (game->player->ppx < game->ray[i].hx)
//             game->ray[i].hs = 1;
//         else
//             game->ray[i].hs = 2;
//     }
//     else
//     {
//         if (game->player->ppx < game->ray[i].hx)
//             game->ray[i].hs = 1;
//         else
//             game->ray[i].hs = 2; 
//     }
// }
// static void vertical_hit(t_game *game, int i)
// {
//     if ((game->player->pa >= 0 && game->player->pa <= PI / 2) || 
//         (game->player->pa >= PI && game->player->pa <= 2 * PI))
//     {
//         if (game->player->ppy < game->ray[i].hy)
//              game->ray[i].hs = 3;
//         else
//             game->ray[i].hs = 4;
//     }
//     else 
//     {
//         if (game->player->ppy < game->ray[i].hy)
//             game->ray[i].hs = 3;
//         else
//             game->ray[i].hs = 4; 
//     }
// }

// void hit_side(t_game *game, int i)
// {
//     if (game->ray[i].hx % 64 == 0 && game->ray[i].hy % 64 == 0)
//         corner_case(game, i);
//     if (game->ray[i].hx % 64 == 0 && game->ray[i].hy % 64 != 0)
//         horizontal_hit(game, i);
//     if (game->ray[i].hy % 64 == 0 && game->ray[i].hx % 64 != 0)
//         vertical_hit(game, i);
// }

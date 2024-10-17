/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:43:13 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/17 15:43:15 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void test_map(t_game *game)
{
    game->map = ft_split("111111111111111-100100000000001-100100000000001-100100010000001-100000000000001-100000000000001-100000000000001-100000000000001-100000000000001-111111111111111", '-'); 
    
    //window->map = ft_split("1111111111-1000100001-1000000001-1000000001-1000000001-1000000001-1000000001-1000000001-1000000001-1111111111", '-'); 
    //window->map = ft_split("11111-10001-10001-10001-11111", '-');
    if (!game->map)
        exit(1);
}

void free_test_map(t_game *game)  
{
    int i = 0;

    while(game->map[i] != NULL)
    {
        free(game->map[i]);
        i ++;
    }
    free(game->map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:03:36 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/09 12:03:38 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

int window()
{
    mlx_t *mlx;

    if (!(mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, true)))       // true: resize on
	{
		return(EXIT_FAILURE);
	}
    mlx_loop(mlx);

    return (0);

}

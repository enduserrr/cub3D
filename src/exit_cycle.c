/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:59:24 by asalo             #+#    #+#             */
/*   Updated: 2024/10/15 10:59:43 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void    err(char *s)
{
	write(2, RB, ft_strlen(RB));
	write(2, "Error: ", ft_strlen("Error: "));
	write(2, W, ft_strlen(W));
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	write(2, RES, ft_strlen(RES));
}

void	exit_cycle(char *s)
{
	int		i;

	if (s)
		err(s);
		mlx_terminate();
	if ()
		free_arr();
	exit (0);
}

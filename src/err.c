/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:02:02 by asalo             #+#    #+#             */
/*   Updated: 2024/10/09 09:02:16 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"

void    write_err(char *s)
{
	write(2, RB, ft_strlen(RB));
	write(2, "Error: ", ft_strlen("Error: "));
	write(2, W, ft_strlen(W));
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	write(2, RES, ft_strlen(RES));
}

void	exit_error(char *s, int state)
{
	// t_map	*map_info;

	// map_info = NULL;
	// write_err(s);
	(void)state;
	write(2, RB, ft_strlen(RB));
	write(2, "Error: ", ft_strlen("Error: "));
	write(2, W, ft_strlen(W));
	write(2, s, ft_strlen(s));
	write(2, "\n", 1);
	write(2, RES, ft_strlen(RES));
	// map_info->exit = state;
}

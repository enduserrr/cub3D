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

/**
 * @brief	Valid player position & starting orientation characters.
 */
int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	is_256(t_txtr *t)
{
	if (!t || !t->c)
		return (1);
	if (t->c->r == 256 || t->c->g == 256 || t->c->b == 256
		|| t->f->r == 256 || t->f->g == 256 || t->f->b == 256)
		return (1);
	return (0);
}

void	invalid_color(t_color *ptr)
{
	ptr->r = 256;
	ptr->g = 256;
	ptr->b = 256;
}

void	txtr_ptrs_init(t_txtr *t)
{
	t->n_txtr = NULL;
	t->s_txtr = NULL;
	t->e_txtr = NULL;
	t->w_txtr = NULL;
	t->gun = NULL;
	t->n_txtr = NULL;
	t->s_txtr = NULL;
	t->e_txtr = NULL;
	t->w_txtr = NULL;
}

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

int	validate_file(char *name)
{
	int	fd;

	if (!name || ft_strlen(name) < 4 || ft_strcmp(name + (ft_strlen(name) - 4),
			".cub"))
		return (write_err(ERROR_MAP_NAME), -1);
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		close(fd);
		return (write_err(ERROR_OPEN), -1);
	}
	close(fd);
	return (fd);
}

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

// void	on_row(int y)
// {
// 	write(1, WB, ft_strlen(WB));
// 	write(1, "[", 1);
// 	write(1, RB, ft_strlen(RB));
// 	write(1, "FAIL", 4);
// 	write(1, WB, ft_strlen(WB));
// 	write(1, "]: ", 3);
// 	write(1, GREY, ft_strlen(GREY));
// 	write(1, "on row ", 8);
// 	ft_putnbr_fd(y, 1);
// 	write(1, "\n", 1);
// 	write(1, RES, ft_strlen(RES));
// }

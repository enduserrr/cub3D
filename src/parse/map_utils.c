#include "../../incs/cub3D.h"

int	surroundings(t_game *game, int y, int x)
{
	if (game->player->is_set != 1)
		return (write_err(ERROR_MAP), 1);
	if ((game->data->map[y][x + 1] == '1' && game->data->map[y][x - 1] == '1'
		&& game->data->map[y + 1][x] == '1'
		&& game->data->map[y - 1][x] == '1')
		|| (game->data->map[y][x + 1] == '2'
		|| game->data->map[y][x - 1] == '2'
		|| game->data->map[y + 1][x] == '2'
		|| game->data->map[y - 1][x] == '2'))
		return (write_err(ERROR_MAP), 1);
	if (y == 0 || ((y == 1 || (size_t)y == game->data->size_y - 2)
			&& (game->data->map[y + 1][x] == ' '
			|| game->data->map[y + 1][x] == '2'
		|| game->data->map[y - 1][x] == ' '
		|| game->data->map[y - 1][x] == '2')))
		return (write_err(ERROR_MAP), 1);
	return (0);
}

int	_plr(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	inval_color(t_txtr *t)
{
	if (!t || !t->c)
		return (1);
	if (t->c->r == 256 || t->c->g == 256 || t->c->b == 256 || t->f->r == 256
		|| t->f->g == 256 || t->f->b == 256)
		return (1);
	return (0);
}

void	set_inval_color(t_color *ptr)
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
	t->dup = false;
}

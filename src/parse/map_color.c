#include "../../incs/cub3D.h"

void	set_color(t_color *ptr, char **colors)
{
	int	i;
	int	tmp;

	tmp = 0;
	i = -1;
	while (++i < 3)
	{
		tmp = atoi_mod(colors[i]);
		if (tmp == -1)
			tmp = 256;
		if (i == 0)
			ptr->r = (unsigned int)tmp;
		else if (i == 1)
			ptr->g = (unsigned int)tmp;
		else if (i == 2)
			ptr->b = (unsigned int)tmp;
	}
	free_arr(colors);
}

/**
 * @brief	Converts a comma-separated string into an RGB color.
 * @param	ptr     Pointer to the t_color struct where the values are stored.
 * @param	line    Comma-separated string representing the color values.
 */
void	str_to_color(t_color *ptr, char *line)
{
	char	**colors;
	int		i;

	colors = splitter(line, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2] || colors[3])
	{
		set_inval_color(ptr);
		free_arr(colors);
		return ;
	}
	i = -1;
	while (colors[++i])
	{
		if (i == 3)
		{
			set_inval_color(ptr);
			free_arr(colors);
			return ;
		}
	}
	set_color(ptr, colors);
}

/**
 * @brief	Extracts floor & ceiling color information.
 * @return	Pointer to the remaining part of the line if not processed,
 *			or NULL otherwise.
 */
char	*colors(t_game *game, char *line)
{
	while (ft_isspace(*line))
		line++;
	if (ft_strncmp(line, "F ", 2) == 0 && !game->textures->f)
	{
		line += 2;
		while (ft_isspace(*line))
			line++;
		game->textures->f = malloc(sizeof(t_color));
		if (!game->textures->f)
			return (line);
		str_to_color(game->textures->f, line);
	}
	else if (ft_strncmp(line, "C ", 2) == 0 && !game->textures->c)
	{
		line += 2;
		while (ft_isspace(*line))
			line++;
		game->textures->c = malloc(sizeof(t_color));
		if (!game->textures->c)
			return (line);
		str_to_color(game->textures->c, line);
	}
	else
		return (line);
	return (NULL);
}

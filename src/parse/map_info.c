/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:18:09 by asalo             #+#    #+#             */
/*   Updated: 2024/10/22 13:18:12 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

static unsigned int  *get_rgb(char *line)
{
    unsigned int  *res;
    int     i;
    int     k;

    i = 0;
    k = 0;
    res = malloc(3 * sizeof(unsigned int));
    if (!res)
        return (NULL);
    while (line[i] && k < 3)
    {
        while (line[i] && (line[i] == ' ' || line[i] == '\t'))
            i++;
        res[k] = (unsigned int)ft_atoi(&line[i]);
        k++;
        while (line[i] && line[i] >= '0' && line[i] <= '9')
            i++;
        while (line[i] && (line[i] == ',' || line[i] == ' '))
            i++;
    }
    if (k != 3)
        return (free(res), NULL);
    return (res);
}

static unsigned int rgb_to_hex(unsigned int *rgb)
{
    int red;
    int green;
    int blue;

    if (!rgb || rgb[0] > 255 || rgb[1] > 255 || rgb[2] > 255)
        return (0);
    red = (int)rgb[0];
    green = (int)rgb[1];
    blue = (int)rgb[2];
    return ((red << 16) | (green << 8) | blue);
}

static void check_info(char *line, t_txtr *textures, int i)
{
    int fd;
    unsigned int *color;

    fd = 0;
    color = 0;
    if (!line || (i != 4 && i != 5))
        return ;
    if (i == 4)
    {
        color = get_rgb(line);
        textures->f = rgb_to_hex(color);
        printf("%x\n", textures->f);
        free(color);
    }
    else if (i == 5)
    {
        color = get_rgb(line);
        textures->c = rgb_to_hex(color);
        printf("%x\n", textures->c);
        free(color);
    }
    return ;
}

void    load_textures(t_txtr *txtr, char *line, int i)
{
    if (!line)
        return ;
    if (i == 0)
        txtr->n_txtr = mlx_load_png(line);
    else if (i == 1)
        txtr->s_txtr = mlx_load_png(line);
    else if (i == 2)
        txtr->w_txtr = mlx_load_png(line);
    else if (i == 3)
        txtr->e_txtr = mlx_load_png(line);
    else if (i == 4 || i == 5)
        check_info(line, txtr, i);
    free(line);
    line = NULL;
    return ;
}

static char *parse_info(char *line, char *result)
{
    while (ft_isspace(*line))
        line++;
    if (ft_strncmp(line, "NO ", 3) == 0)
        result = ft_strdup(line + 3);
    else if (ft_strncmp(line, "SO ", 3) == 0)
        result = ft_strdup(line + 3);
    else if (ft_strncmp(line, "WE ", 3) == 0)
        result = ft_strdup(line + 3);
    else if (ft_strncmp(line, "EA ", 3) == 0)
        result = ft_strdup(line + 3);
    else if (ft_strncmp(line, "F ", 2) == 0)
        result = ft_strdup(line + 2);
    else if (ft_strncmp(line, "C ", 2) == 0)
        result = ft_strdup(line + 2);
    else
        return ((NULL));
    return (result);
}

/**
 * @brief   Extract color and texture info from file and delete them from map.
 *          Add func to put info straight into mlx_ strings and int array
 *          (with rgb->hex conversion)
 */
int get_info(t_game *game)
{
    int     i;
    int     k;
    char    **tmp;
    char    *line;

    line = NULL;
    tmp = game->map_info->map;
    k = 0;
    while (tmp[k])
    {
        if ((line = parse_info(tmp[k], line)) == NULL)
            break ;
        load_textures(game->textures, line, k);
        free(tmp[k]);
        tmp[k] = NULL;
        k++;
    }
    i = 0;
    while (tmp[k])
        tmp[i++] = tmp[k++];
    tmp[i] = NULL;
    game->map_info->map = tmp;
    // for (int l = 0; game->map_info->map[l];)
	// 	printf("%s\n", game->map_info->map[l++]);
    return (0);
}

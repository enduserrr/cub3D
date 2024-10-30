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



/**
 * @brief	Validate texture files and paths and colors.
 */

/*
// static int check_info(t_txtr *txtrs)
// {
//     int i;
//     int fd;
//     int floor;
//     int ceiling;
//     i = 0;
//     fd = 0;
//     floor = ft_atoi(txtrs->info[4]);
//     ceiling = ft_atoi(txtrs->info[5]);
//     if ((ceiling < 0 || ceiling > 255) || (floor < 0 || floor > 255))
//         return (write_err("incorrect color info"), 1);
//     while (i < 4)
//     {
//         if (!txtrs->info[i] || (fd = open(txtrs->info[i], O_RDONLY) < 0) || close(fd))
//             return (write_err("unable to open the texture files"), 1);
//         i++;
//     }
//     return (0);
// }*/

static int check_info(char **arr, t_game *game)
{
    int i;
    int fd;
    unsigned int *floor;
    unsigned int *ceiling;

    i = 0;
    fd = 0;
    floor = get_rgb(arr[4]);
    ceiling = get_rgb(arr[5]);
    // if (!floor || !ceiling || ceiling > 255 || floor > 255)
    //     return (write_err("incorrect color info"), 1);
    game->textures->f = rgb_to_hex(floor);
    game->textures->c = rgb_to_hex(ceiling);
    // printf("%x\n", game->textures->c);
    // printf("%x\n", game->textures->f);
    free(floor);
    free(ceiling);
    // while (i < 4)
    // {
    //     if (!txtrs->info[i] || (fd = open(txtrs->info[i], O_RDONLY) < 0) || close(fd))
    //         return (write_err("unable to open the texture files"), 1);
    //     i++;
    // }
    return (0);
}

/**
 * @brief   Removes white space (almost well) and saves the texture file paths
 *          into t_txtr struct array.
*/
static void *parse_info(char *line, char **arr)
{
    while (ft_isspace(*line))
        line++;
    if (ft_strncmp(line, "NO ", 3) == 0)
        arr[0] = ft_strdup(line + 3);
    else if (ft_strncmp(line, "SO ", 3) == 0)
        arr[1] = ft_strdup(line + 3);
    else if (ft_strncmp(line, "WE ", 3) == 0)
        arr[2] = ft_strdup(line + 3);
    else if (ft_strncmp(line, "EA ", 3) == 0)
        arr[3] = ft_strdup(line + 3);
    else if (ft_strncmp(line, "F ", 2) == 0)
        arr[4] = ft_strdup(line + 2);
    else if (ft_strncmp(line, "C ", 2) == 0)
        arr[5] = ft_strdup(line + 2);
    else
        return ((void *)1);
    return (NULL);
}

/**
 * @brief   Extract color and texture info from file and delete them from temp_map.
 *          Add func to put info straight into mlx_ strings and int array
 *          (with rgb->hex conversion)
 */
/*// int get_info(t_game *game)
// {
//     int     i;
//     int     k;
//     char    **tmp;

//     game->textures->info = malloc(6 * sizeof(char *));
//     i = -1;
//     while (++i < 6)
//         game->textures->info[i] = NULL;
//     tmp = game->map_info->temp_map;
//     k = -1;
//     while (tmp[++k])
//     {
//         if (parse_info(tmp[k], game->textures->info) != NULL)
//             break ;
//         free(tmp[k]);
//         tmp[k] = NULL;
//     }
//     i = 0;
//     while (tmp[k])
//         tmp[i++] = tmp[k++];
//     tmp[i] = NULL;
//     game->map_info->temp_map = tmp;
//     if (check_info(game->textures))
//         return (1);
//     return (0);
// }*/

/* Change to have exit loop.*/
void load_textures(t_txtr *txtr, char **arr)
{
    txtr->n_txtr = mlx_load_png(arr[0]);
    if (!txtr->n_txtr)
        exit(12);
    txtr->s_txtr = mlx_load_png(arr[1]);
    if (!txtr->s_txtr)
        exit(12);
    txtr->w_txtr = mlx_load_png(arr[2]);
    if (!txtr->w_txtr)
        exit(12);
    txtr->e_txtr = mlx_load_png(arr[3]);
    if (!txtr->e_txtr)
        exit(12);
}

int get_info(t_game *game)
{
    int     i;
    int     k;
    char    **tmp;
    char    **new;

    if (!(new = malloc(6 * sizeof(char *))))
        return (write_err("malloc error"), 1);
    i = -1;
    while (++i < 6)
        new[i] = NULL;
    tmp = game->map_info->temp_map;
    k = -1;
    while (tmp[++k])
    {
        if (parse_info(tmp[k], new) != NULL)
            break ;
        free(tmp[k]);
        tmp[k] = NULL;
    }
    i = 0;
    while (tmp[k])
        tmp[i++] = tmp[k++];
    tmp[i] = NULL;
    game->map_info->temp_map = tmp;
    if (check_info(new, game))
        return (free_arr(new), 1);
    load_textures(game->textures, new);
    return (free_arr(new), 0);
}

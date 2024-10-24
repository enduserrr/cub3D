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

/**
 * @brief	Validate texture files and paths and colors.
 */

static int check_info(t_txtr *txtrs)
{
    int i;
    int fd;
    int floor;
    int ceiling;

    i = 0;
    fd = 0;
    floor = ft_atoi(txtrs->info[4]);
    ceiling = ft_atoi(txtrs->info[5]);
    if ((ceiling < 0 || ceiling > 255) || (floor < 0 || floor > 255))
        return (write_err("incorrect color info"), 1);
    /*checks for valid file and path*/
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
 */
int get_info(t_map *map_info, t_txtr  *txtrs)
{
    int     i;
    int     k;
    char    **tmp;

    i = -1;
    while (++i < 6)
        txtrs->info[i] = NULL;
    tmp = map_info->temp_map;
    k = -1;
    while (tmp[++k])
    {
        if (parse_info(tmp[k], txtrs->info) != NULL)
            break;
    }
    i = 0;
    while (tmp[k])
        tmp[i++] = tmp[k++];
    tmp[i] = NULL;
    map_info->temp_map = tmp;
    if (check_info(txtrs))
        return (1);
    i = -1;
    while (txtrs->info[++i])
        printf("Info[%d]: %s\n", i, txtrs->info[i]);
    return (0);
}


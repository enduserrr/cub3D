/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:25:30 by asalo             #+#    #+#             */
/*   Updated: 2024/10/08 11:25:50 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/cub3D.h"

void    err(char *s)
{
    while (*s)
        write(2, s++, 1);
}

int check_map(char *name)
{
    int fd;

    if (!name || ft_strlen(name) < 4 ||
        ft_strcmp(name + (ft_strlen(name) - 4), ".cub"))
        return (err("error: invalid map\n"), -1);
    fd = open(name, O_RDONLY);
    if (fd < 0)
        return (err("error: unable to open the file\n"), -1);
    return (fd);
}

int main(int ac, char **av)
{
    int fd;
    t_data  *data;

    data = malloc(sizeof(t_data));
    if (ac != 2)
        return (err("error: invalid arg count\n"), 1);
    if (check_map(av[1]) < 0)
        exit(1);
    return (0);
}

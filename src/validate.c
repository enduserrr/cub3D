/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 09:36:45 by asalo             #+#    #+#             */
/*   Updated: 2024/10/17 09:36:49 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"


/*void	arg_check(char *s, int nb_types[6], int *index, int i)
{
	if (!ft_strncmp(s, "NO", 2))
		parse_dir(s, 0, &nb_types[0]);
	else if (!ft_strncmp(s, "SO", 2))
		parse_dir(s, 2, &nb_types[2]);
	else if (!ft_strncmp(s, "WE", 2))
		parse_dir(s, 1, &nb_types[1]);
	else if (!ft_strncmp(s, "EA", 2))
		parse_dir(s, 3, &nb_types[3]);
	else if (!ft_strncmp(s, "F", 1))
		parse_color(s, 0, &nb_types[4]);
	else if (!ft_strncmp(s, "C", 1))
		parse_color(s, 1, &nb_types[5]);
	else if (count_args(nb_types) && *index == -1)
		*index = i;
	else if (!is_empty(s) && !is_map(s))
	{
		printf("Error\n%s invalid argument\n", s);
		ft_black_hole(0);
	}
}*/

int is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	is_valid(char c)
{
	if (is_player(c) || ft_isspace(c) || c == '1' || c == '0')
		return (1);
	return (0);
}

char	*ft_strjoin_mod(char *free_line, char const *s1, char const *s2)
{
	size_t	len;
	char	*ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc(sizeof(char) * len + 1);
	if (!(ptr))
	{
		free(free_line);
		return (NULL);
	}
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[j])
		ptr[i++] = s2[j++];
	ptr[i] = ('\0');
	free(free_line);
	return (ptr);
}

void	rows(char *s, size_t len, t_map *map_info)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (is_valid(s[i]))
		{
			if (is_player(s[i]))
				map_info->start_orientation = s[i];
			i++;
		}
		if (ft_isspace(s[i]))
			i++;
		else
			return (err("row error 2"), exit(1));
	}
}

void	first_row(char *s, t_map *map_info)
{
	size_t	i;
	size_t	len;

	i = 0;
	map_info->size_x = 0;
	while (s[i])
	{
		len = ft_strlen(s[i]) - i;
		if (len > map_info->size_x)
			map_info->size_x = len;
		if (s[i] != 1 || (ft_strlen(s[i]) - 1) != '1')
			return (err("first_row error"), map_info->exit = 1);
		i++;
	}
}
void handle_spaces(char *s, t_map *map_info)
{
    int		i;
    int		j;
    char	last;

	i = 0;
	j = 0;
	last = '\0';
    while (s[i] && ft_isspace((unsigned char)s[i]))
        i++;
	if (s[i] != '1')
		return (err("map error"), map_info->exit = 1);
    while (s[i])
    {
		if (!is_player(s[i]) && s[i] != ' ' && s[i] != '0' && s[i] != '1')
			return (err("map error"), map_info->exit = 1);
        if (is_player(s[i]) || s[i] == '0' || s[i] == '1')
            last = s[i];
        if (s[i] == ' ')
			s[i] == '0';
        s[j++] = s[i++];
    }
    if (last != '1')
		return (err("map error"), map_info->exit = 1);
    s[j] = '\0';
}

void	basic_check(char **map, t_map *map_info)
{
	size_t	i;
	size_t	len;

	i = 0;
	map_info->size_y = 0;
	while (map[i])
	{
		handle_spaces(map[i], map_info);/*remove white space*/
		if (map_info->exit != 0)/*follow exit flag*/
			return (err("random error"), free_arr(map), exit(map_info->exit));
		if (i == 0)
			first_row(map[i], map_info);/*handle first row*/
		else
			rows(map[i], len, map_info);/*go through rest of the rows*/
		map_info->size_y++;/*increment row count*/
		i++;
	}
	// first_row(map[i - 1], map_info);
}

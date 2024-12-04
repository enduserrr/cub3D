/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_mod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 12:48:00 by asalo             #+#    #+#             */
/*   Updated: 2024/11/03 12:48:26 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

static char	*init_gnl(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	while (stash[i])
		i++;
	i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, i);
	line[i] = '\0';
	return (line);
}

static size_t	find_end(char *line)
{
	size_t	i;

	i = 0;
	if (!line)
		return (-1);
	while (i < 4095)
	{
		if (line[i] == '\0')
			return (i + 1);
		i++;
	}
	return (i);
}

static char	*handle_read(char *line, char *stash, char *buffer, size_t read_check)
{
	strlcpy_modi(stash, &buffer[find_end(buffer)], 4095 + 1);
	buffer[read_check] = '\0';
	line = strjoin_modi(line, buffer);
	return (line);
}

static char	*gnl_extract(char *line, char *stash, int fd)
{
	char	buffer[4095 + 1];
	ssize_t	read_check;
	size_t	total_read;

	total_read = ft_strlen(line);
	while (total_read < 4096)
	{
		ft_bzero(buffer, 4095 + 1);
		read_check = read(fd, buffer, 4095);
		if (read_check == -1)
			return (free(line), ft_bzero(stash, 4095 + 1), NULL);
		if (total_read + read_check > 4096)
			read_check = 4096 - total_read;
		line = handle_read(line, stash, buffer, read_check);
		total_read += read_check;
		if (read_check == 0)
			break ;
	}
	if (total_read >= 4096)
		return (free(line), ft_bzero(stash, 4095 + 1), NULL);
	return (line);
}

char	*gnl_mod(int fd)
{
	static char	stash[4095];
	char		*line;

	if (fd < 0)
		return (NULL);
	line = init_gnl(stash);
	if (!line)
		return (NULL);
	strlcpy_modi(stash, &stash[1], 4095 + 1);
	line = gnl_extract(line, stash, fd);
	if (!line || line[0] == '\0' || ft_strlen(line) > 4096)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

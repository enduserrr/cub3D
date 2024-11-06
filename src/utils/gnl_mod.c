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

static void	strlcpy_modi(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
}

static char	*init_gnl(char *stash, int *eof)
{
	size_t	i;
	char	*line;

	i = 0;
	(void)eof;
	while (stash[i])
		i++;
	i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, stash, i);
	line[i] = '\0';
	// if (i > 0 && line[i - 1] == '\n')
	// 	*eof = i - 1;
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

static char	*gnl_extract(char *line, char *stash, int *eof, int fd)
{
	char	buffer[4095 + 1];
	ssize_t	read_check;
	size_t	file_size;

	(void)eof;
	read_check = 0;
	while (read_check < 4095)
	{
		ft_bzero(buffer, (4095 + 1));
		read_check = read(fd, buffer, 4095);
		if (read_check == -1 || read_check > 4095)
		{
			free(line);
			ft_bzero(stash, (4095 + 1));
			return (NULL);
		}
		file_size = find_end(buffer);
		strlcpy_modi(stash, &buffer[file_size], (4095 + 1));
		buffer[file_size] = '\0';
		line = strjoin_mod(line, buffer, eof);
		if (read_check == 0)
		{
			ft_bzero(stash, 4095 + 1);
			break ;
		}
	}
	return (line);
}

char	*gnl_mod(int fd)
{
	static char	stash[4095];
	char		*line;
	static int			eof;

	if (fd < 0)
		return (NULL);
	eof = -1;
	line = init_gnl(stash, &eof);
	if (!line)
		return (NULL);
	strlcpy_modi(stash, &stash[eof + 1], 4095 + 1);
	line = gnl_extract(line, stash, &eof, fd);
	// if (!line || line[0] == '\0')
	if (line == (void *)1 || line[0] == '\0') /*Changed*/
	{
		free(line);
		return (NULL);
	}
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:08:03 by asalo             #+#    #+#             */
/*   Updated: 2024/12/12 10:08:37 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3D.h"

static void	clear_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	if (!s[0])
		return (0);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		else
		{
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		if (s[i])
			i++;
	}
	return (count);
}

static int	start_point(const char *s, char c, int w)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c && count++ == w)
			return (i);
		else if (s[i] != c)
		{
			if (count == w)
				return (i);
			while (s[i] && s[i] != c)
				i++;
			count++;
		}
		if (s[i])
			i++;
	}
	return (i);
}

static int	w_len(const char *s, char c, int w)
{
	int	i;

	i = start_point(s, c, w);
	if (s[i] == c)
		return (1);
	while (s[i] && s[i] != c)
		i++;
	return (i - start_point(s, c, w));
}

char	**splitter(const char *s, char c)
{
	int		i;
	int		wc;
	char	**new;

	if (!s)
		return (NULL);
	wc = word_count(s, c);
	new = ft_calloc(wc + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		new[i] = ft_substr(s, start_point(s, c, i), w_len(s, c, i));
		if (!new[i])
			return (clear_arr(new), NULL);
		i++;
	}
	return (new);
}

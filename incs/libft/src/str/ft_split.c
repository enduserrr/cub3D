/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:49:45 by asalo             #+#    #+#             */
/*   Updated: 2024/08/08 11:38:37 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

static int	word_count(const char *s, char c)
{
	int	i;
	int	count;

	if (!s[0])
		return (0);
	if (c == '\0')
		return (ft_strlen(s));
	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
			i++;
		count++;
	}
	return (count - (s[i - 1] == c));
}

static int	start_point(const char *s, char c, int w)
{
	int	i;

	if (c == '\0')
		return (w);
	i = 0;
	while (s[i] == c)
		i++;
	while (w)
	{
		while (s[i] != c)
			i++;
		while (s[i] == c)
			i++;
		w--;
	}
	return (i);
}

static int	w_len(const char *s, char c, int w)
{
	int	i;
	int	a;

	if (c == '\0')
		return (1);
	i = start_point(s, c, w);
	a = i;
	while (s[i] && s[i] != c)
		i++;
	return (i - a);
}

char	**ft_split(const char *s, char c)
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
			return (NULL);
		i++;
	}
	return (new);
}

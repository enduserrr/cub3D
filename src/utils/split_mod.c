/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 13:46:44 by asalo             #+#    #+#             */
/*   Updated: 2024/11/03 13:46:46 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/cub3D.h"

/*// static int	w_count(const char *s, char c)
// {
// 	int	i;
// 	int	count;

// 	if (!s[0])
// 		return (0);
// 	if (c == '\0')
// 		return (ft_strplen(s));
// 	i = 0;
// 	count = 0;
// 	while (s[i])
// 	{
// 		while (s[i] && s[i] == c)
// 			i++;
// 		while (s[i] && s[i] != c)
// 			i++;
// 		count++;
// 	}
// 	return (count - (s[i - 1] == c));
// }
static int	w_count(const char *s, char c)
{
	int	i;
	int	count;

	if (!s[0])
		return (ft_strplen(s));
	if (c == '\0')
		return (ft_strplen(s));
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

static int	starting_point(const char *s, char c, int w)
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

// static int	w_length(const char *s, char c, int w)
// {
// 	int	i;
// 	int	a;

// 	if (c == '\0')
// 		return (1);
// 	i = starting_point(s, c, w);
// 	a = i;
// 	while (s[i] && s[i] != c)
// 		i++;
// 	return (i - a);
// }

static int	w_length(const char *s, char c, int start)
{
	int	i;

	i = 0;
	while (*s && (s[start] == c))
		start++;
	while (*s && (s[start] != c))
	{
		i++;
		start++;
	}
	return (i);
}

// static void	free_split(char **arr, int size)
// {
// 	int	i;

// 	i = 0;
// 	while (i < size)
// 		free(arr[i]);
// 	free(arr);
// }

char	**ft_split_mod(char *s, char c)
{
	int		i;
	// int		j;
	int		wc;
	char	**new;

	if (!s)
		return (NULL);
	wc = w_count(s, c);
	new = ft_calloc(wc + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < wc)
	{
		new[i] = ft_substr(s, starting_point(s, c, i), (size_t)w_length(s, c, i));
		printf("%s\n", new[i]);
		// if (!new[i])
		// {
		// 	free_split(new, i);
		// 	return (NULL);
		// }
		i++;
	}
	return (new);
}*/

static int	countingstrings(char const *s, char c)
{
	size_t	i;
	int		result;

	result = 0;
	i = 0;
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			while (s[i + 1] != c && s[i + 1] != '\0')
				i++;
			result++;
		}
		i++;
	}
	// printf("%i\n", result);
	return (result);
}

char	**ft_split_mod(char const *s, char c)
{
	char	**result;
	size_t	start;
	size_t	i;
	int		j;

	i = 0;
	start = 0;
	j = 0;
	result = malloc(sizeof(char *) * (countingstrings(s, c) + 1));
	if (!result)
		return (0);
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			while (s[i + 1] != c && s[i + 1] != '\0')
				i++;
			result[j] = malloc(sizeof(char) * (i - start + 2));
			ft_strlcpy(result[j], &s[start], i - start + 2);
			j++;
		}
		i++;
		start = i;
	}
	result[j] = NULL;
	// j = 0;
	// while (result[j])
	// 	printf("%s\n", result[j++]);
	return (result);
}

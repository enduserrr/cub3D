/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:05:54 by asalo             #+#    #+#             */
/*   Updated: 2024/07/20 18:59:03 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	i;

	i = ft_strlen(s1);
	if (i == 0)
		i++;
	dup = ft_calloc(i + 1, sizeof(char));
	if (!dup)
		return (NULL);
	ft_memcpy(dup, s1, i);
	dup[i] = '\0';
	return (dup);
}

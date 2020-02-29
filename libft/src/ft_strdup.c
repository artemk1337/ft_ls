/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:49:00 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 12:45:56 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*s2;
	size_t	i;
	size_t	n;

	n = ft_strlen(src);
	i = 0;
	if (!(s2 = ft_strnew(n)))
		return (NULL);
	while (src[i] && i < n)
	{
		s2[i] = src[i];
		i++;
	}
	return (s2);
}

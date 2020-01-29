/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 18:48:50 by cchadwic          #+#    #+#             */
/*   Updated: 2019/09/06 21:30:01 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(const char *s1, const char *s2)
{
	int str;

	str = 0;
	while (s1[str] != '\0' && s2[str] != '\0')
	{
		if (s1[str] != s2[str])
			return ((unsigned char)s1[str] - (unsigned char)s2[str]);
		str++;
	}
	return ((unsigned char)s1[str] - (unsigned char)s2[str]);
}

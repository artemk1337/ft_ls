/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_dop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:19:12 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/08 22:29:15 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int		ft_abs(int a)
{
	return ((a) < 0 ? -(a) : (a));
}

int		ft_max(int a, int b)
{
	return ((a >= b) ? (a) : (b));
}

int		len_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	put_filename(t_ls *ls, char *tmp)
{
	ls->buffer[(ls->i)++] = ' ';
	while (*tmp)
		ls->buffer[(ls->i)++] = *(tmp++);
}

void	put_flags(t_ls *ls, char **av)
{
	ls->flags = 1;
	if (*((av)[1]) == 'a')
		ls->a = 1;
	else if (*((av)[1]) == 'l')
		ls->l = 1;
	else if (*((av)[1]) == 'R')
		ls->rr = 1;
	else if (*((av)[1]) == 'r')
		ls->r = 1;
	else if (*((av)[1]) == 't')
		ls->t = 1;
	else if (*((av)[1]) == 'u')
		ls->u = 1;
	else if (*((av)[1]) == '1')
		ls->one = 1;
	else if (*((av)[1]) == 'x')
		ls->x = 1;
	else if (*((av)[1]) == 'S')
		ls->s = 1;
	else
		error(3, &(*((av)[1])));
}

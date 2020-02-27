/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:50:49 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/27 19:18:09 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_ls *g_ls;

void		get_col(t_path *curr_d, int *max_size, int *columns)
{
	int k;

	if (g_ls->rr == 1)
		show_flag_r(curr_d);
	*max_size = curr_d->info->max_len;
	k = get_columns();
	*columns = 1;
	while (((*max_size) * (*columns) + (*columns)) <= k)
		(*columns)++;
	(*columns)--;
}

void		main_dop(t_ls *ls, int ac, char **av)
{
	int	i;

	if (ac == 1)
	{
		if (!(ls->arr = malloc(sizeof(t_path *) * 2)))
			ERROR(1);
		ls->arr[0] = init_path(".");
		ls->arr[1] = NULL;
	}
	else if (ac > 1)
	{
		if (!(ls->arr = malloc(sizeof(t_path *) * (ac))))
			ERROR(1);
		i = -1;
		while (++i < ac - 1)
			ls->arr[i] = init_path(av[i]);
		ls->arr[i] = NULL;
	}
}

int			main(int ac, char **av)
{
	t_ls		*ls;
	t_path		*curr;
	int			i;

	ls = init_ls();
	if (ac != 1)
		av = check_flags(ls, av);
	if (ls->flags == 1)
		ac--;
	main_dop(ls, ac, av);
	if (ac == 1)
		get_files(ls, ls->arr[0]);
	else
	{
		i = -1;
		while (ls->arr[++i])
			get_files(ls, (curr = ls->arr[i]));
	}
	exit(0);
}

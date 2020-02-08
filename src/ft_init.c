/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:27:02 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/08 22:25:29 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_files		*init_files(void)
{
	t_files	*a;

	if (!(a = malloc(sizeof(t_files))))
		ERROR(1);
	a->filename = NULL;
	a->len_name = 0;
	a->next = NULL;
	return (a);
}

t_info		*init_info(void)
{
	t_info *a;

	if (!(a = malloc(sizeof(t_info))))
		ERROR(1);
	a->total = 0;
	a->max_len_owner = 0;
	a->max_len_group = 0;
	a->max_len_links = 0;
	a->max_len_size = 0;
	a->max_len = 0;
	a->max_len_time = 0;
	return (a);
}

t_path		*init_path(char *path)
{
	t_path *a;

	if (!(a = malloc(sizeof(t_path))))
		ERROR(1);
	a->next = NULL;
	if (!(a->path = ft_strdup(path)))
		ERROR(1);
	a->dir_name = NULL;
	a->depth = 0;
	a->info = init_info();
	a->files = NULL;
	return (a);
}

t_ls		*init_ls(void)
{
	t_ls	*ls;

	if (!(ls = malloc(sizeof(t_ls))))
		ERROR(1);
	ls->a = 0;
	ls->l = 0;
	ls->rr = 0;
	ls->r = 0;
	ls->t = 0;
	ls->u = 0;
	ls->s = 0;
	ls->one = 0;
	ls->x = 0;
	ls->flags = 0;
	ls->i = 0;
	ls->arr = NULL;
	ls->max_len_time = 12;
	return (ls);
}

char		**check_flags(t_ls *ls, char **av)
{
	if (av[1][0] != '-')
		return (&(av[1]));
	if (!(av[1][1]))
		error(2, (av)[1]);
	(av[1])++;
	while (*((av)[1]))
	{
		put_flags(ls, av);
		((av)[1])++;
	}
	return (&(av[2]));
}

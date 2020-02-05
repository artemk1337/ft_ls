/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iuolo <iuolo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:26:36 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/04 19:01:24 by iuolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		get_files(t_ls *ls, t_path *curr_d)
{
	DIR				*dir;
	t_files			*curr_f;
	int				counter;

	g_ls = ls;
	if (curr_d->depth == 0)
		curr_d->dir_name = ft_strdup(curr_d->path);
	else
		curr_d->dir_name = ft_strdup(ft_short_name(curr_d->path));
	lstat(curr_d->path, &(curr_d->stats));
	if (!(dir = check_dir_and_permission(curr_d)))
		return ;
	curr_f = g_f_check_a(ls, curr_d);
	counter = g_f_read_files(ls, curr_d, curr_f, dir);
	closedir(dir);
	curr_f = curr_d->files;
	if (ls->l == 1)
		ft_print_l(curr_d);
	else if (ls->one == 1)
		ft_print_1(curr_d, curr_f);
	else if (ls->x == 1)
		ft_print_x(counter, curr_d, curr_f);
	else
		ft_print_stand(counter, curr_d, curr_f);
	g_f_rec(ls, curr_d, curr_f);
}

void		g_f_rec(t_ls *ls, t_path *curr_d, t_files *curr_f)
{
	t_path	*tmp_d;
	t_files *tmp_f;

	curr_f = curr_d->files;
	while (curr_f)
	{
		tmp_d = curr_d;
		if (S_ISDIR(curr_f->stats.st_mode) &&
		ft_strcmp((const char *)curr_f->filename, (const char *)"..") != 0 &&
		ft_strcmp((const char *)curr_f->filename, (const char *)".") != 0 &&
		ls->rr == 1)
		{
			ft_putchar('\n');
			curr_d->next = init_path(convert_filename(
				prepare_path(tmp_d->path), curr_f->filename));
			curr_d->next->depth = tmp_d->depth + 1;
			curr_d->next->info->max_len_size = 0;
			get_files(ls, curr_d->next);
		}
		curr_d = tmp_d;
		tmp_f = curr_f;
		curr_f = curr_f->next;
		free(tmp_f);
	}
}

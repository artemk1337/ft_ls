/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_files.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:26:36 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 13:13:44 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		vivod(int counter, t_path *curr_d, t_files *curr_f)
{
	if (g_ls->p == 1)
		flag_p(curr_d);
	if (g_ls->l == 1)
		ft_print_l(curr_d);
	else if (g_ls->one == 1)
		ft_print_1(curr_d, curr_f);
	else if (g_ls->x == 1)
		ft_print_x(counter, curr_d, curr_f);
	else
		ft_print_stand(counter, curr_d, curr_f);
}

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
	curr_f = curr_d->files;
	vivod(counter, curr_d, curr_f);
	g_f_rec(ls, curr_d, curr_f);
}

void		cleaner(t_path *curr_d)
{
	t_path	*c_p_cl;
	t_files	*c_f_cl;
	t_files	*c_f_cl_f;

	c_p_cl = curr_d->next;
	free(curr_d->next->dir_name);
	free(curr_d->next->path);
	free(curr_d->next->info);
	c_f_cl = curr_d->next->files;
	while (c_f_cl)
	{
		free(c_f_cl->filename);
		c_f_cl_f = c_f_cl->next;
		free(c_f_cl);
		c_f_cl = c_f_cl_f;
	}
	free(c_p_cl);
}

void		g_f_rec(t_ls *ls, t_path *curr_d, t_files *curr_f)
{
	t_path	*tmp_d;
	t_files *tmp_f;
	char	*s;

	curr_f = curr_d->files;
	while (curr_f)
	{
		tmp_d = curr_d;
		if (S_ISDIR(curr_f->stats.st_mode) && ft_strcmp((const char *)
		curr_f->filename, (const char *)"..") != 0 && ft_strcmp((const char *)
		curr_f->filename, (const char *)".") != 0 && ls->rr == 1)
		{
			ft_putchar('\n');
			s = convert_filename(prepare_path(tmp_d->path), curr_f->filename);
			curr_d->next = init_path(s);
			free(s);
			curr_d->next->depth = curr_d->depth + 1;
			curr_d->next->info->max_len_size = 0;
			get_files(ls, curr_d->next);
			cleaner(curr_d);
		}
		curr_d = tmp_d;
		tmp_f = curr_f;
		curr_f = curr_f->next;
	}
}

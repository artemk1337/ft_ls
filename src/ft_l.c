/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_l.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:19:01 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 12:56:35 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		l_put(t_ls *ls, t_files *curr_f, t_path *curr_d)
{
	char	*s;

	put_mode(ls, curr_f->stats, s = convert_filename(
		prepare_path(curr_d->path), curr_f->filename));
	free(s);
	put_smth(ls, s = ft_itoa(curr_f->stats.st_nlink),
	&(curr_d->info->max_len_links), 1);
	free(s);
	put_owner(ls, getpwuid((uid_t)(curr_f->stats.st_uid))->pw_name,
	&(curr_d->info->max_len_owner), 1);
	put_owner(ls, getgrgid((gid_t)(curr_f->stats.st_gid))->gr_name,
	&(curr_d->info->max_len_group), 2);
	put_smth(ls, s = ft_itoa(curr_f->stats.st_size),
	&(curr_d->info->max_len_size), 2);
	free(s);
	put_date(ls, return_time(ls, curr_f->stats));
	put_filename(ls, curr_f->filename);
	ls->buffer[(ls->i)] = '\0';
	ft_putstr(ls->buffer);
}

void		l_dop(t_ls *ls, t_path *curr_d, t_files *curr_f)
{
	int		i;
	char	s_tmp[PATH_MAX];
	char	*s;

	i = -1;
	while (++i < PATH_MAX)
		s_tmp[i] = '\0';
	while (curr_f)
	{
		l_put(ls, curr_f, curr_d);
		s = convert_filename(prepare_path(curr_d->path), curr_f->filename);
		i = readlink(s, NULL, 0);
		free(s);
		if (i >= 0)
		{
			ft_putstr(" -> ");
			readlink(s = convert_filename(prepare_path(curr_d->path),
			curr_f->filename), s_tmp, PATH_MAX);
			free(s);
			ft_putstr(s_tmp);
		}
		ft_putchar('\n');
		ls->i = 0;
		curr_f = curr_f->next;
	}
}

void		ft_print_l(t_path *curr_d)
{
	t_files	*curr_f;
	t_ls	*ls;
	char	*s;

	ls = g_ls;
	curr_f = curr_d->files;
	curr_d->info->total += curr_d->stats.st_blocks;
	while (curr_f)
	{
		curr_d->info->total += (int)curr_f->stats.st_blocks;
		curr_f = curr_f->next;
	}
	curr_f = curr_d->files;
	if (ls->rr == 1 && check_args(curr_d->path, ls->arr))
		show_flag_r(curr_d);
	ft_putstr("total ");
	ft_putstr(s = ft_itoa(curr_d->info->total));
	free(s);
	ft_putchar('\n');
	l_dop(ls, curr_d, curr_f);
}

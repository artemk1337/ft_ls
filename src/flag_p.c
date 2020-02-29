/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:35:26 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 13:19:41 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		flag_p(t_path *curr_d)
{
	t_files	*curr_p;
	char	*s;

	curr_d->info->max_len += 1;
	curr_p = curr_d->files;
	while (curr_p)
	{
		if (S_ISDIR(curr_p->stats.st_mode))
		{
			s = ft_strjoin(curr_p->filename, "/");
			free(curr_p->filename);
			curr_p->filename = s;
		}
		curr_p = curr_p->next;
	}
}

static void	dop(t_ls *ls, t_path *curr_d)
{
	int		tmp;
	char	*s;

	s = ft_itoa(curr_d->stats.st_nlink);
	if (curr_d->info->max_len_links < (tmp = ft_strlen(s)))
		curr_d->info->max_len_links = tmp;
	if (s)
		free(s);
	if (curr_d->info->max_len_owner <
		(tmp = ft_strlen(getpwuid((uid_t)(curr_d->stats.st_uid))->pw_name)))
		curr_d->info->max_len_owner = tmp;
	if (curr_d->info->max_len_group <
		(tmp = ft_strlen(getgrgid((gid_t)(curr_d->stats.st_gid))->gr_name)))
		curr_d->info->max_len_group = tmp;
	s = ft_itoa(curr_d->stats.st_size);
	if (curr_d->info->max_len_size < (tmp = ft_strlen(s)))
		curr_d->info->max_len_size = tmp;
	if (s)
		free(s);
	if (curr_d->info->max_len_time <
		(tmp = get_size_time(return_time(ls, curr_d->stats))))
		curr_d->info->max_len_time = tmp;
}

t_files		*g_f_check_a(t_ls *ls, t_path *curr_d)
{
	t_files	*curr_f;

	if (ls->a == 1)
	{
		dop(ls, curr_d);
		curr_d->files = init_files();
		curr_f = curr_d->files;
		curr_f->filename = ft_strdup(".");
		curr_f->len_name = 1;
		curr_f->stats = curr_d->stats;
	}
	else
		curr_f = curr_d->files;
	return (curr_f);
}

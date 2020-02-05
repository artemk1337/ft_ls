/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:25:29 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/04 18:25:46 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

static void	dop(t_ls *ls, t_path *curr_d)
{
	int	tmp;

	if (curr_d->info->max_len_links <
		(tmp = ft_strlen(ft_itoa(curr_d->stats.st_nlink))))
		curr_d->info->max_len_links = tmp;
	if (curr_d->info->max_len_owner <
		(tmp = ft_strlen(getpwuid((uid_t)(curr_d->stats.st_uid))->pw_name)))
		curr_d->info->max_len_owner = tmp;
	if (curr_d->info->max_len_group <
		(tmp = ft_strlen(getgrgid((gid_t)(curr_d->stats.st_gid))->gr_name)))
		curr_d->info->max_len_group = tmp;
	if (curr_d->info->max_len_size <
		(tmp = ft_strlen(ft_itoa(curr_d->stats.st_size))))
		curr_d->info->max_len_size = tmp;
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

void		g_f_read_files_cheack_stat(t_ls *ls, t_files *curr_f,
t_path *curr_d)
{
	int	tmp;

	lstat(convert_filename(prepare_path(curr_d->path), curr_f->filename),
	&(curr_f->stats));
	if (curr_d->info->max_len_links <
	(tmp = ft_strlen(ft_itoa(curr_f->stats.st_nlink))))
		curr_d->info->max_len_links = tmp;
	if (curr_d->info->max_len <
	(tmp = ft_strlen(curr_f->filename)))
		curr_d->info->max_len = tmp;
	if (curr_d->info->max_len_owner <
	(tmp = ft_strlen(getpwuid((uid_t)(curr_f->stats.st_uid))->pw_name)))
		curr_d->info->max_len_owner = tmp;
	if (curr_d->info->max_len_group <
	(tmp = ft_strlen(getgrgid((gid_t)(curr_f->stats.st_gid))->gr_name)))
		curr_d->info->max_len_group = tmp;
	if (curr_d->info->max_len_size <
	(tmp = ft_strlen(ft_itoa(curr_f->stats.st_size))))
		curr_d->info->max_len_size = tmp;
	if (curr_d->info->max_len_time <
	(tmp = get_size_time(return_time(ls, curr_f->stats))))
		curr_d->info->max_len_time = tmp;
}

t_files		*g_f_read_files_1(t_files *curr_f, t_path *curr_d)
{
	if (!(curr_f))
	{
		curr_d->files = init_files();
		curr_f = curr_d->files;
	}
	else
	{
		while (curr_f->next)
			curr_f = curr_f->next;
		curr_f->next = init_files();
		curr_f = curr_f->next;
	}
	return (curr_f);
}

int			g_f_read_files(t_ls *ls, t_path *curr_d, t_files *curr_f, DIR *dir)
{
	int				tmp;
	int				counter;
	struct dirent	*entry;

	entry = readdir(dir);
	tmp = 0;
	counter = 0;
	while ((entry = readdir(dir)))
	{
		if ((ls->a == 1 || file_hide(entry->d_name) == 0) &&
		ft_strcmp(entry->d_name, ".") != 0)
		{
			curr_f = g_f_read_files_1(curr_f, curr_d);
			curr_f->filename = ft_strdup(ft_short_name(entry->d_name));
			curr_f->len_name = ft_strlen(curr_f->filename);
			g_f_read_files_cheack_stat(ls, curr_f, curr_d);
			counter++;
		}
	}
	counter += (ls->a == 1) ? 1 : 0;
	if (counter > 1)
		curr_d->files = sort_files(ls, curr_d->files, counter);
	return (counter);
}

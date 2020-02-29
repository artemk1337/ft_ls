/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:25:29 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 13:17:51 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

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

static void	g_f_read_files_check_st_dop(t_ls *ls, t_files *curr_f,
t_path *curr_d)
{
	char	*s;
	int		tmp;

	s = ft_itoa(curr_f->stats.st_size);
	if (curr_d->info->max_len_size < (tmp = ft_strlen(s)))
		curr_d->info->max_len_size = tmp;
	if (s)
		free(s);
	if (curr_d->info->max_len_time <
	(tmp = get_size_time(return_time(ls, curr_f->stats))))
		curr_d->info->max_len_time = tmp;
}

void		g_f_read_files_check_stat(t_ls *ls, t_files *curr_f,
t_path *curr_d)
{
	int		tmp;
	char	*s;

	s = NULL;
	lstat(s = convert_filename(prepare_path(curr_d->path), curr_f->filename),
	&(curr_f->stats));
	if (s)
		free(s);
	s = ft_itoa(curr_f->stats.st_nlink);
	if (curr_d->info->max_len_links < (tmp = ft_strlen(s)))
		curr_d->info->max_len_links = tmp;
	if (s)
		free(s);
	if (curr_d->info->max_len <
	(tmp = ft_strlen(curr_f->filename)))
		curr_d->info->max_len = tmp;
	if (curr_d->info->max_len_owner <
	(tmp = ft_strlen(getpwuid((uid_t)(curr_f->stats.st_uid))->pw_name)))
		curr_d->info->max_len_owner = tmp;
	if (curr_d->info->max_len_group <
	(tmp = ft_strlen(getgrgid((gid_t)(curr_f->stats.st_gid))->gr_name)))
		curr_d->info->max_len_group = tmp;
	g_f_read_files_check_st_dop(ls, curr_f, curr_d);
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
	DIR				*dir_cp;

	dir_cp = dir;
	tmp = 0;
	counter = 0;
	while ((entry = readdir(dir)))
	{
		if ((ls->a == 1 || file_hide(entry->d_name) == 0) &&
		ft_strcmp(entry->d_name, ".") && (++counter))
		{
			curr_f = g_f_read_files_1(curr_f, curr_d);
			curr_f->filename = ft_strdup(ft_short_name(entry->d_name));
			curr_f->len_name = ft_strlen(curr_f->filename);
			g_f_read_files_check_stat(ls, curr_f, curr_d);
		}
	}
	dir = dir_cp;
	counter += (ls->a == 1) ? 1 : 0;
	closedir(dir);
	if (counter > 1)
		curr_d->files = sort_files(ls, curr_d->files, counter);
	return (counter);
}

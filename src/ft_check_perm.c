/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_perm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:25:54 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 14:18:04 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

int			check_args(char *name, t_path **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i]->path, name) == 0)
			return (0);
		i++;
	}
	return (1);
}

int			check_permission(struct stat stats)
{
	if (stats.st_mode & !S_IWUSR)
		return (1);
	else if (stats.st_mode & S_IWUSR & !S_IXUSR)
		return (2);
	return (0);
}

int			check_permission_for_dir(t_path *curr_d)
{
	if (S_ISREG(curr_d->stats.st_mode) ||
		S_ISDIR(curr_d->stats.st_mode) ||
		S_ISLNK(curr_d->stats.st_mode) ||
		S_ISCHR(curr_d->stats.st_mode) ||
		S_ISBLK(curr_d->stats.st_mode) ||
		S_ISFIFO(curr_d->stats.st_mode) ||
		S_ISSOCK(curr_d->stats.st_mode))
	{
		if (check_permission(curr_d->stats) == 2)
			return (1);
		else
		{
			error(1, curr_d->path);
			return (1);
		}
	}
	return (0);
}

DIR			*check_dop(DIR *dir, t_path *curr_d)
{
	if (S_ISDIR(curr_d->stats.st_mode))
	{
		if (!(dir) && check_permission_for_dir(curr_d) == 0)
			error(2, curr_d->path);
	}
	else
	{
		if (check_permission(curr_d->stats) == 2)
			return (NULL);
		else if (check_permission(curr_d->stats) == 1)
		{
			error(1, curr_d->path);
			return (NULL);
		}
	}
	return (dir);
}

DIR			*check_dir_and_permission(t_path *curr_d)
{
	DIR *dir;

	dir = opendir(curr_d->path);
	if (S_ISREG(curr_d->stats.st_mode) ||
		S_ISDIR(curr_d->stats.st_mode) ||
		S_ISLNK(curr_d->stats.st_mode) ||
		S_ISCHR(curr_d->stats.st_mode) ||
		S_ISBLK(curr_d->stats.st_mode) ||
		S_ISFIFO(curr_d->stats.st_mode) ||
		S_ISSOCK(curr_d->stats.st_mode))
	{
		dir = check_dop(dir, curr_d);
	}
	else
	{
		if (!(dir) && check_permission_for_dir(curr_d) == 0)
			error(2, curr_d->path);
	}
	return (dir);
}

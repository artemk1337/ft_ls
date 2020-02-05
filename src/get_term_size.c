/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_term_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iuolo <iuolo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:28:54 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/04 19:23:41 by iuolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void	show_flag_r(t_path *curr_d)
{
	ft_putstr(curr_d->path);
	ft_putstr(":");
	ft_putchar('\n');
}

int		get_columns(void)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	return (w.ws_col);
}

int		file_hide(char *file)
{
	if (*file == '.')
		return (1);
	return (0);
}

int		get_size_time(time_t time_)
{
	int		i;
	int		start;

	i = 7;
	start = i;
	if (ABS(difftime(time(NULL), time_)) >= 15768000)
	{
		start = 15;
		i = 21;
	}
	else
		i = 13;
	return (i - start);
}

size_t	return_time(t_ls *ls, struct stat stats)
{
	if (ls->u == 1)
		return (stats.st_atime);
	return (stats.st_mtime);
}

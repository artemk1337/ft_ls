/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 12:35:26 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/29 13:17:56 by cchadwic         ###   ########.fr       */
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

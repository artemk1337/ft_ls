/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_other.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:27:53 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/27 16:29:18 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		ft_print_1(t_path *curr_d, t_files *curr_f)
{
	t_ls *ls;

	ls = g_ls;
	if (ls->rr == 1)
		show_flag_r(curr_d);
	curr_f = curr_d->files;
	while (curr_f)
	{
		ft_putstr(curr_f->filename);
		ft_putstr("\n");
		curr_f = curr_f->next;
	}
}

void		x_dop(int lines, int columns, int max_size, char **arr)
{
	int i_lines;
	int k;
	int i;

	i_lines = 0;
	while (i_lines < lines)
	{
		k = 0;
		while (k < columns && arr[i_lines * columns + k])
		{
			i = 0;
			while (arr[i_lines * columns + k][i])
				g_ls->buffer[(g_ls->i)++] = arr[i_lines * columns + k][i++];
			while (i++ <= max_size)
				g_ls->buffer[(g_ls->i)++] = ' ';
			k++;
		}
		g_ls->buffer[(g_ls->i)++] = '\0';
		ft_putstr(g_ls->buffer);
		ft_putchar('\n');
		g_ls->i = 0;
		i_lines++;
	}
}

void		ft_print_x(int counter, t_path *curr_d, t_files *curr_f)
{
	int		max_size;
	int		columns;
	int		lines;
	char	**arr;
	int		i;

	columns = *get_col(curr_d, &max_size, &columns);
	lines = counter / columns + ((counter % columns > 0) ? 1 : 0);
	if (!(arr = malloc(sizeof(char *) * (counter + 1))))
		ERROR(1);
	arr[counter] = NULL;
	curr_f = curr_d->files;
	i = 0;
	while (curr_f)
	{
		arr[i++] = curr_f->filename;
		curr_f = curr_f->next;
	}
	x_dop(lines, columns, max_size, arr);
	free(arr);
}

void		flag_p(t_path *curr_d)
{
	t_files *curr_p;

	curr_d->info->max_len += 1;
	curr_p = curr_d->files;
	while (curr_p)
	{
		if (S_ISDIR(curr_p->stats.st_mode))
			curr_p->filename = ft_strjoin(curr_p->filename, "/");
		curr_p = curr_p->next;
	}
}

void		stand_dop(int lines, int columns, int max_size, char **arr)
{
	int l;
	int count_columns;
	int len;
	int i;

	l = 0;
	len = len_arr(arr);
	while (l < lines)
	{
		count_columns = 0;
		while (count_columns * lines + l < len && count_columns < columns)
		{
			i = 0;
			while (arr[count_columns * lines + l][i])
				g_ls->buffer[(g_ls->i)++] = arr[count_columns * lines + l][i++];
			while (i++ <= max_size)
				g_ls->buffer[(g_ls->i)++] = ' ';
			count_columns++;
		}
		g_ls->buffer[(g_ls->i)++] = '\0';
		ft_putstr(g_ls->buffer);
		ft_putchar('\n');
		g_ls->i = 0;
		l++;
	}
}

void		ft_print_stand(int counter, t_path *curr_d, t_files *curr_f)
{
	int		max_size;
	int		columns;
	int		lines;
	char	**arr;
	int		i;

	columns = *get_col(curr_d, &max_size, &columns);
	lines = counter / columns + ((counter % columns > 0) ? 1 : 0);
	if (!(arr = malloc(sizeof(char *) * (counter + 1))))
		ERROR(1);
	arr[counter] = NULL;
	curr_f = curr_d->files;
	i = 0;
	while (curr_f)
	{
		arr[i++] = curr_f->filename;
		curr_f = curr_f->next;
	}
	stand_dop(lines, columns, max_size, arr);
	free(arr);
}

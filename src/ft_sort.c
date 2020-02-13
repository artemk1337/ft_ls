/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:28:33 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/08 22:24:11 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

t_files		*revive_files(t_files **arr)
{
	t_files *start;
	int		i;
	t_files *tmp;

	i = 0;
	start = arr[0];
	tmp = start;
	while (arr[++i])
	{
		tmp->next = arr[i];
		tmp = tmp->next;
	}
	tmp->next = NULL;
	return (start);
}

void		sort_files_t(t_files **arr, int max)
{
	int		i;
	t_files	*tmp;

	i = 0;
	while (max--)
	{
		i = 0;
		while (arr[i + 1] != NULL)
		{
			if (arr[i]->stats.st_mtime - arr[i + 1]->stats.st_mtime < 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
			i++;
		}
	}
}

void		sort_files_l(t_files **arr, int max)
{
	int		i;
	t_files	*tmp;

	i = 0;
	while (max--)
	{
		i = 0;
		while (arr[i + 1] != NULL)
		{
			if (ft_strcmp(arr[i]->filename, arr[i + 1]->filename) > 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
			i++;
		}
	}
}

void		sort_files_s(t_files **arr, int max)
{
	int		i;
	t_files *tmp;

	i = 0;
	while (max--)
	{
		i = 0;
		while (arr[i + 1] != NULL)
		{
			if (arr[i]->stats.st_size - arr[i + 1]->stats.st_size < 0)
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
			i++;
		}
	}
}

t_files		*sort_files(t_ls *ls, t_files *start, int max)
{
	int		i;
	t_files	**arr;
	t_files	*tmp;

	if (!(arr = (t_files **)malloc(sizeof(t_files *) * (max + 1))))
		ERROR(1);
	arr[max] = NULL;
	i = 0;
	tmp = start;
	while (i < max)
	{
		arr[i++] = tmp;
		tmp = tmp->next;
	}
	if (ls->s == 1)
		sort_files_s(arr, max);
	else if (ls->t == 1)
		sort_files_t(arr, max);
	else
		sort_files_l(arr, max);
	start = revive_files(arr);
	if (ls->r == 1)
		return (reverse_order_files(start));
	return (start);
}

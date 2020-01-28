/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 21:50:49 by cchadwic          #+#    #+#             */
/*   Updated: 2020/01/28 21:50:51 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/ft_ls.h"
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <stdio.h>

int     main(int ac, char **av)
{
	t_ls        *ls;
	struct stat *tmp;

	tmp = NULL;
	ls = init_ls(ac, av);
	if (ac == 1)
		show_dir(ls);
	else
	{
		check_flags(ls);
		show_dir(ls);
		printf("%d", lstat("src", tmp));
	}
	return (0);
}


/*
 * a - unvisible files
 * l - format
 * R - recursive all files in folders
 * r - sort in reverse order
 * t - sort time
*/


void    check_flags(t_ls *ls)
{
	if (*((ls->av)[1]) != '-')
		return;
	while (*((ls->av)[1]))
	{
		ls->flags = 1;
		if (*((ls->av)[1]) == 'a')
			ls->a = 1;
		else if (*((ls->av)[1]) == 'l')
			ls->l = 1;
		else if (*((ls->av)[1]) == 'R')
			ls->R = 1;
		else if (*((ls->av)[1]) == 'r')
			ls->r = 1;
		else if (*((ls->av)[1]) == 't')
			ls->t = 1;
		((ls->av)[1])++;
	}
}


t_ls    *init_ls(int ac, char **av)
{
	t_ls    *ls;

	if (!(ls = malloc(sizeof(t_ls))))
		ERROR;
	ls->av = av;
	ls->ac = ac;
	ls->a = 0;
	ls->l = 0;
	ls->R = 0;
	ls->r = 0;
	ls->t = 0;
	ls->flags = 0;
	return (ls);
}


void    show_dir(t_ls *ls)
{
	ls->a = 0;
	return ;
}

void    error(t_ls *ls)
{
	free(ls);
	exit(1);
}



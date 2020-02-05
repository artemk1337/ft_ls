/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iuolo <iuolo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:26:25 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/04 19:03:10 by iuolo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		error(int code, char *file)
{
	if (code == 1)
	{
		ft_putstr("ls: ");
		ft_putstr(file);
		ft_putstr(": Permission denied\n");
		return ;
	}
	else if (code == 2)
	{
		ft_putstr("ls: ");
		ft_putstr(file);
		ft_putstr(": No such file or directory\n");
		return ;
	}
	else if (code == 3)
	{
		ft_putstr("ls: ");
		ft_putstr("illegal option -- ");
		ft_putchar(*file);
		ft_putchar('\n');
		ft_putstr("usage: ls \
		[-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	}
	exit(1);
}

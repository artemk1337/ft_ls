/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 22:10:32 by cchadwic          #+#    #+#             */
/*   Updated: 2020/01/28 22:11:27 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_LS_H_
# define _FT_LS_H_

# define ERROR error(ls)

typedef struct	s_ls
{
	int             flags;
	int             a;
	int             l;
	int             R;
	int             r;
	int             t;

	char            **av;
	char            ac;
}				t_ls;

int             main(int ac, char **av);
void            check_flags(t_ls *ls);
t_ls            *init_ls(int ac, char **av);
void            show_dir(t_ls *ls);
void            error(t_ls *ls);




#endif

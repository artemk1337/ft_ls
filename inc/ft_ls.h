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

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <time.h>

# define BUFF_SIZE 1024

/*
struct stat {
	dev_t     st_dev;          ID устройства с файлом
	ino_t     st_ino;          номер inode
	mode_t    st_mode;         права доступа
	nlink_t   st_nlink;        кол-во жёстких ссылок
	uid_t     st_uid;          ID пользователя-владельца
	gid_t     st_gid;          ID группы-владельца
	dev_t     st_rdev;         ID устройства (если это спец. файл)
	off_t     st_size;         полный размер в байтах
	blksize_t st_blksize;      размер блока ввода-вывода
                                 файловой системы
	blkcnt_t  st_blocks;       кол-во выделенных блоков по 512Б
};
*/

typedef struct	s_ls
{
	int             flags;
	int             a;
	int             l;
	int             R;
	int             r;
	int             t;

	char            buffer[BUFF_SIZE];
	int             i;
	unsigned int    total;

	char            **av;
	char            ac;
	struct          stat stats;
}				t_ls;

int             main(int ac, char **av);
void            check_flags(t_ls *ls);
t_ls            *init_ls(int ac, char **av);
void            show_dir(t_ls *ls);
void            error(t_ls *ls);
void            put_mode(t_ls *ls);
void			put_link(t_ls *ls);




#endif

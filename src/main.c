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
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include <stdio.h>

/*
int main(int argc, char **argv)
{
	if(argc != 2)
		return 1;

	struct stat fileStat;

	if(stat(argv[1], &fileStat) < 0)
		return 1;

	printf("Information for %s\n",argv[1]);
	printf("---------------------------\n");
	printf("File Size: \t\t%lld bytes\n",fileStat.st_size);
	printf("Number of Links: \t%d\n",fileStat.st_nlink);
	printf("File inode: \t\t%lld\n",fileStat.st_ino);

	printf("File Permissions: \t");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
	printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
	printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
	printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
	printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
	printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
	printf("\n\n");

	printf("The file %s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");

	return 0;
}
*/




int     main(int ac, char **av)
{
	t_ls        *ls;

	ls = init_ls(ac, av);
	if (ac == 1)
		show_dir(ls);
	else
	{
		check_flags(ls);
		show_dir(ls);
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
	ls->i = 0;
	ls->total = 0;
	return (ls);
}


void    show_dir(t_ls *ls)
{
	int i;

	i = 0;
	while (++i < ls->ac)
	{
		lstat("src", &(ls->stats));
		put_mode(ls);

		ls->buffer[(ls->i)] = '\0';
		printf("%d", ls->stats.st_dev);
		printf("%s", ls->buffer);

		// free(&(ls->stats));
	}
}

void    put_mode(t_ls *ls)
{
	struct  stat fileStat;

	fileStat = ls->stats;
	ls->buffer[(ls->i)++] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
}

void    error(t_ls *ls)
{
	free(ls);
	exit(1);
}



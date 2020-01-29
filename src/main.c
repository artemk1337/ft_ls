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
 * a - invisible files
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


// Будет работать иначе
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
	ls->max_len_owner = 0;
	ls->max_len_group = 0;
	ls->max_len_links = 0;
	ls->max_len_size = 0;
	ls->max_len_time = 12;
	return (ls);
}



// Будет работать иначе
void    show_dir(t_ls *ls)
{
	int		i;
	char	*filename;
	
	i = 0;
	while (++i < ls->ac)
	{
		filename = "src";
		put_line_with_l(ls, (const char *)filename);

		printf("%s\n", ls->buffer);

		// free(&(ls->stats));
	}
}


// Будет работать иначе
void	put_line_with_l(t_ls *ls, const char *filename)
{
	stat(filename, &(ls->stats));
	put_mode(ls);
	put_smth(ls, ft_itoa(ls->stats.st_nlink), &(ls->max_len_links)); // Put links
	put_smth(ls, getpwuid((uid_t)(ls->stats.st_uid))->pw_name, &(ls->max_len_owner)); // Put owner
	put_smth(ls, getgrgid((gid_t)(ls->stats.st_gid))->gr_name, &(ls->max_len_group)); // Put group
	put_smth(ls, ft_itoa(ls->stats.st_size), &(ls->max_len_size)); // Put size
	put_date(ls);
	put_filename(ls, filename);

	ls->buffer[(ls->i)] = '\0';
}


int		get_columns(void)
{
	struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	// printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);
	return (w.ws_col);
}

void	put_smth(t_ls *ls, char *tmp, int *ls_len)
{
	int		len;

	ls->buffer[(ls->i)++] = ' ';
	len = ft_strlen(tmp);
	if (len >= *ls_len)
		*ls_len = len;
	else
		while (++len <= *ls_len)
			ls->buffer[(ls->i)++] = ' ';
	while (*tmp)
		ls->buffer[(ls->i)++] = *(tmp++);
}

void	put_date(t_ls *ls)
{
	char	*tmp;
	int		i;
	time_t	time_;

	i = -1;
	ls->buffer[(ls->i)++] = ' ';
	time_ = ls->stats.st_mtime;
	tmp = &(ctime(&time_)[4]);
	while (++i < 7)
		ls->buffer[(ls->i)++] = tmp[i];
	i--;
	// if >= полгода
	if (ABS(difftime(time(NULL), time_)) >= 15768000 && (i = 15))
		while (++i < 20)
			ls->buffer[(ls->i)++] = tmp[i];
	while (++i < 12)
		ls->buffer[(ls->i)++] = tmp[i];
}

void	put_filename(t_ls *ls, const char *filename)
{
	int i;

	i = -1;
	ls->buffer[(ls->i)++] = ' ';
	while (filename[++i])
		ls->buffer[(ls->i)++] = filename[i];
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



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

//#include <sys/syslimits.h>

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







t_files		*init_files(void)
{
	t_files	*a;

	if (!(a = malloc(sizeof(t_files))))
		ERROR;
	a->filename = NULL;
	a->len_name = 0;
	a->next = NULL;
	return (a);
}



t_info		*init_info(void)
{
	t_info *a;

	if (!(a = malloc(sizeof(t_info))))
		ERROR;
	a->total = 0;
	a->max_len_owner = 0;
	a->max_len_group = 0;
	a->max_len_links = 0;
	a->max_len_size = 0;
	a->max_len = 0;
	return (a);
}

t_path		*init_path(char *path)
{
	t_path *a;

	if (!(a = malloc(sizeof(t_path))))
		ERROR;
	
	a->next = NULL;

	if (!(a->path = ft_strdup(path)))
		ERROR;
	a->dir_name = NULL;
	a->len_name = 0;
	a->depth = 0;

	a->info = init_info();
	a->files = NULL;
	return (a);
}










char		*ft_short_name(char *path)
{
	int i;
	int k;

	i = 0;
	while (path[i])
		i++;
	i--;
	while (path[i] == '/' && i > 0)
		path[i--] = '\0';
	i = 0;
	k = 0;
	while (path[i])
	{
		if (path[i] == '/' && i > 0)
			k = i + 1;
		i++;
	}
	return (&(path[k]));
}

char        *convert_filename(char *s1, char *s2)
{
	int i;
	int k;

	i = -1;
	while (s1[++i])
		;
	k = -1;
	while (s2[++k])
		s1[i++] = s2[k];
	s1[i] = '\0';
	// printf("CONVERT %s\n", s1);
	return (s1);
}



char        *prepare_path(char *s)
{
	char    *s1;
	int     i;
	int     k;
	int     sign;

	// ft_putstr("PREPARE PATH START\n");
	i = 0;
	k = 0;
	sign = 0;
	if (!(s1 = ft_strnew(PATH_MAX)))
		ERROR;
	while (s[i])
	{
		if (s[i] != '/')
		{
			sign = 0;
			s1[k++] = s[i++];
		}
		else if (s[i] == '/')
		{
			if (sign == 0)
			{
				sign = 1;
				s1[k++] = s[i++];
			}
			else
				i++;
		}
	}
	if (sign == 0)
		s1[k] = '/';
	// printf("%s\n", s1);
	// ft_putstr("PREPARE PATH END\n");
	return (s1);
}

int			file_hide(char *file)
{
	if (*file == '.')
		return (1);
	return (0);
}













// Perfect
t_files		*reverse_order_files(t_files *start)
{
	t_files	*curr;
	t_files	*next;
	t_files	*prev;

	curr = start;
	prev = NULL;
	while (curr)
	{
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return (prev);
}

















t_files		*sort_files(t_ls *ls, t_files *start, int max)
{
	ls = ls;
	start = start;
	max = max;
	int		i;

	t_files	**arr;
	t_files	*tmp;


	if (!(arr = (t_files **)malloc(sizeof(t_files *) * (max + 1))))
		ERROR;
	arr[max] = NULL;
	i = 0;
	tmp = start;
	while (i < max)
	{
		ft_putstr((arr[i++] = tmp));
		ft_putstr("\n");
	}

	
	




	if (ls->r == 1)
		return(reverse_order_files(start));
	return (start);
}




void		get_files(t_ls *ls, t_path *curr_d)
{
	DIR             *dir;
	struct dirent   *entry;
	
	t_files			*curr_f;
	t_path			*tmp_d;
	int				tmp;

	// printf("\n\tOPEN DIR %s \tDEPTH - %d \n\n", curr_d->path, curr_d->depth);
	stat(curr_d->path, &(curr_d->stats)); // STAT! Not stats!
	if (curr_d->depth == 0)
		curr_d->dir_name = ft_strdup(curr_d->path);
	else
		curr_d->dir_name = ft_strdup(ft_short_name(curr_d->path));
	curr_d->len_name = ft_strlen(curr_d->dir_name); // Correct!
	// printf("dir enter %s 1\n", curr_d->path);


	if (curr_d->info->max_len_links < (tmp = ft_strlen(ft_itoa(curr_d->stats.st_nlink))))
		curr_d->info->max_len_links = tmp;
	if (curr_d->info->max_len_owner < (tmp = ft_strlen(getpwuid((uid_t)(curr_d->stats.st_uid))->pw_name)))
		curr_d->info->max_len_owner = tmp;
	if (curr_d->info->max_len_group < (tmp = ft_strlen(getgrgid((gid_t)(curr_d->stats.st_gid))->gr_name)))
		curr_d->info->max_len_group = tmp;
	if (curr_d->info->max_len_size < (tmp = ft_strlen(ft_itoa(curr_d->stats.st_size))))
		curr_d->info->max_len_size = tmp;
	// printf("dir enter %s 2\n", curr_d->path);


	/// TEST START

	dir = opendir(curr_d->path);
	if (!dir)
		ERROR; // Error for open dir
	entry = readdir(dir);
	if (ls->a == 1)
	{
		curr_d->files = init_files();
		curr_f = curr_d->files;
		curr_f->filename = ft_strdup(".");
		curr_f->len_name = 1;
		curr_f->stats = curr_d->stats;
	}
	else
		curr_f = curr_d->files;
	tmp = 0;
	while ((entry = readdir(dir)))
	{
		if ((ls->a == 1 || file_hide(entry->d_name) == 0) && ft_strcmp(entry->d_name, ".") != 0)
		{
			if (!(curr_f))
				curr_f = (curr_d->files = init_files());
			else
			{
				while (curr_f->next)
					curr_f = curr_f->next;
				curr_f = (curr_f->next = init_files());
			}
			curr_f->filename = ft_strdup(ft_short_name(entry->d_name));
			curr_f->len_name = ft_strlen(curr_f->filename);
			stat(convert_filename(prepare_path(curr_d->path), curr_f->filename), &(curr_f->stats));
			tmp++;
		}
	}
	closedir(dir);

	if (tmp > 1)
		curr_d->files = sort_files(ls, curr_d->files, tmp);


	/// TEST END



	/*
	dir = opendir(curr_d->path);
	if (!dir)
		ERROR;
	// printf("dir enter %s 3\n", curr_d->path);
	entry = readdir(dir);
	// printf("%s\n", curr_d->dir_name);
	if (ls->a == 1)
	{
		curr_d->files = init_files();
		curr_f = curr_d->files;
		curr_f->filename = ft_strdup(".");
		curr_f->len_name = 1;
		curr_f->stats = curr_d->stats;
	}
	else
		curr_f = curr_d->files;
	while ((entry = readdir(dir)))
	{
		// printf("DIR: %s FN: %s \n", curr_d->dir_name, entry->d_name);
		if ((ls->a == 1 || file_hide(entry->d_name) == 0) && ft_strcmp(entry->d_name, ".") != 0)
		{
			if (!(curr_f))
				curr_f = (curr_d->files = init_files());
			else
			{
				while (curr_f->next)
					curr_f = curr_f->next;
				curr_f = (curr_f->next = init_files());
			}
			curr_f->filename = ft_strdup(ft_short_name(entry->d_name));
	*/

	/// NEW

	curr_f = curr_d->files;
	while(curr_f)
	{
		// printf("Current file: \t%s\n", curr_f->filename);

		//printf("Current path: %s\n", curr_d->path);
		//printf("DIR: %s FN: %s FullName: %s 0\n", curr_d->dir_name, curr_f->filename, convert_filename(prepare_path(curr_d->path), curr_f->filename));
		//printf("Current file %s \t\t Full path to file: %s\n", curr_f->filename, convert_filename(prepare_path(curr_d->path), curr_f->filename));


		// Сравнение названия
		if (curr_d->info->max_len_links < (tmp = ft_strlen(ft_itoa(curr_f->stats.st_nlink))))
			curr_d->info->max_len_links = tmp;
		if (curr_d->info->max_len < (tmp = ft_strlen(curr_f->filename)))
			curr_d->info->max_len = tmp;
		if (curr_d->info->max_len_owner < (tmp = ft_strlen(getpwuid((uid_t)(curr_f->stats.st_uid))->pw_name)))
			curr_d->info->max_len_owner = tmp;
		if (curr_d->info->max_len_group < (tmp = ft_strlen(getgrgid((gid_t)(curr_f->stats.st_gid))->gr_name)))
			curr_d->info->max_len_group = tmp;
		if (curr_d->info->max_len_size < (tmp = ft_strlen(ft_itoa(curr_f->stats.st_size))))
			curr_d->info->max_len_size = tmp;

		//printf("DIR: %s FN: %s 1\n", curr_d->dir_name, curr_f->filename);

		tmp_d = curr_d;
		if (S_ISDIR(curr_f->stats.st_mode) && ft_strcmp((const char *)curr_f->filename, (const char *)"..") != 0 && ls->R == 1)
		{
			while (curr_d->next)
				curr_d = curr_d->next;
			// printf("Enter in: %s\n", convert_filename(prepare_path(tmp_d->path), curr_f->filename));
			curr_d->next = init_path(convert_filename(prepare_path(tmp_d->path), curr_f->filename));
			curr_d->next->depth = tmp_d->depth + 1;
			get_files(ls, curr_d->next);
		}
		curr_d = tmp_d;
		//printf("DIR: %s FN: %s \n", curr_d->dir_name, curr_f->filename);
		//printf("DIR: %s FN: %s 2\n", curr_d->dir_name, curr_f->filename);
		curr_f = curr_f->next;
	}

	closedir(dir);
	// printf("\n\tCLOSE DIR %s \tDEPTH - %d \n\n", curr_d->path, curr_d->depth);
}


/*
void		sort_files(t_ls *ls)
{
	t_path		*tmp_d;
	t_path		*curr_d;
	t_files		*curr_f;
	int			i;
	
	i = -1;
	while (ls->arr[++i])
	{
		curr_d = ls->arr[i];
		if (ls->a != 1)
		{
			tmp_d = curr_d;
		}
	}
}
*/




void		print_dirs(t_ls *ls)
{
	t_path	*curr_d;
	// t_files	*curr_file;
	int		i;

	i = -1;
	while (ls->arr[++i])
	{
		curr_d = ls->arr[i];
		show_dir(ls, curr_d);
	}

}








int     main(int ac, char **av)
{
	t_ls        *ls;
	t_path		*curr;
	int			i;

	ls = init_ls();	
	if (ac != 1)
		av = check_flags(ls, av);
	if (ls->flags == 1)
		ac--;
	// Здесь выделил память под сруктуры аргументов.
	/*
	* Выделяю память. В каждой ячейке лежит указатель на структуру с директорией.
	* Если директорий не подано, то будет одна директория "."
	*/
	if (ac == 1)
	{
		if (!(ls->arr = malloc(sizeof(t_path *) * 2)))
			ERROR;
		ls->arr[0] = init_path(".");
		ls->arr[1] = NULL;
	}
	else if (ac > 1)
	{
		if (!(ls->arr = malloc(sizeof(t_path *) * (ac))))
			ERROR;
		i = -1;
		while (++i < ac - 1)
			ls->arr[i] = init_path(av[i]);
		ls->arr[i] = NULL;
	}
	if (ac == 1)
		get_files(ls, ls->arr[0]);
	else
	{
		i = -1;
		while (ls->arr[++i])
		{
			curr = ls->arr[i];
			get_files(ls, curr);
		}
	}
	print_dirs(ls);
	return (0);
}










/*
 * a - invisible files						OK!
 * l - format
 * R - recursive all files in folders		OK!
 * r - sort in reverse order
 * t - sort time
*/


char		**check_flags(t_ls *ls, char **av)
{
	if (av[1][0] != '-')
		return (&(av[1]));
	if (!(av[1][1]))
		return (&(av[1]));
	(av[1])++;
	while (*((av)[1]))
	{
		ls->flags = 1;
		if (*((av)[1]) == 'a')
			ls->a = 1;
		else if (*((av)[1]) == 'l')
			ls->l = 1;
		else if (*((av)[1]) == 'R')
			ls->R = 1;
		else if (*((av)[1]) == 'r')
			ls->r = 1;
		else if (*((av)[1]) == 't')
			ls->t = 1;
		else
			ERROR;
		((av)[1])++;
	}
	return (&(av[2]));
}


t_ls    *init_ls(void)
{
	t_ls    *ls;

	if (!(ls = malloc(sizeof(t_ls))))
		ERROR;
	ls->a = 0;
	ls->l = 0;
	ls->R = 0;
	ls->r = 0;
	ls->t = 0;
	ls->flags = 0;
	ls->i = 0;
	ls->arr = NULL;
	ls->max_len_time = 12;
	return (ls);
}










void    show_dir(t_ls *ls, t_path *curr_d)
{
	while (curr_d)
	{
		if (ls->l == 1)
			put_line_with_l(ls, curr_d);
		if (ls->l == 0)
			put_line_without(ls, curr_d);
		curr_d = curr_d->next;
		if (curr_d)
			ft_putstr("\n");
	}
}



void		show_flag_R(t_path *curr_d)
{
	ft_putstr(curr_d->path);
	ft_putstr(":");
	ft_putchar('\n');
}



void	put_line_without(t_ls *ls, t_path *curr_d)
{
	t_files		*curr_f;
	// t_files		*tmp_f;
	int			width;

	ls = ls;
	curr_f = curr_d->files;
	curr_f = curr_f;
	width = get_columns();
	printf("%d\n", width);
	printf("%d\n", curr_d->info->max_len);
	printf("%ld\n", curr_d->stats.st_nlink);
	printf("%d\n", ft_strcmp(".", ".."));

}



void	put_line_with_l(t_ls *ls, t_path *curr_d)
{
	t_files		*curr_f;
	// t_files		*tmp_f;

	// Count total
	curr_f = curr_d->files;
	curr_d->info->total += curr_d->stats.st_blocks;
	while (curr_f)
	{
		curr_d->info->total += (int)curr_f->stats.st_blocks;
		//printf("%s - total - %ld\n", curr_f->filename, curr_f->stats.st_blocks);
		curr_f = curr_f->next;
	}
	curr_f = curr_d->files;

	if (ls->R == 1)
		show_flag_R(curr_d);

	ft_putstr("total ");
	ft_putstr(ft_itoa(curr_d->info->total / 2));
	ft_putchar('\n');

	while (curr_f)
	{
		put_mode(ls, curr_f->stats); // Correct
		put_smth(ls, ft_itoa(curr_f->stats.st_nlink), &(curr_d->info->max_len_links)); // Put links. Corect.
		put_smth(ls, getpwuid((uid_t)(curr_f->stats.st_uid))->pw_name, &(curr_d->info->max_len_owner)); // Put owner. Correct
		put_smth(ls, getgrgid((gid_t)(curr_f->stats.st_gid))->gr_name, &(curr_d->info->max_len_group)); // Put group. Correct
		put_smth(ls, ft_itoa(curr_f->stats.st_size), &(curr_d->info->max_len_size)); // Put size. Correct
		put_date(ls, curr_f->stats.st_mtime); // Date. Correct
		put_smth(ls, curr_f->filename, &(curr_d->info->max_len)); // Filename. Correct

		ls->buffer[(ls->i)] = '\0';
		ft_putstr(ls->buffer);
		ft_putchar('\n');
		ls->i = 0;
		curr_f = curr_f->next;
	}
}

















// Correct
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
	int		i;

	i = -1;
	ls->buffer[(ls->i)++] = ' ';
	len = ft_strlen(tmp);
	while (++len <= *ls_len)
		ls->buffer[(ls->i)++] = ' ';
	while (tmp[++i])
		ls->buffer[(ls->i)++] = tmp[i];
}

void	put_date(t_ls *ls, time_t time_)
{
	char	*tmp;
	int		i;

	i = -1;
	ls->buffer[(ls->i)++] = ' ';
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

void    put_mode(t_ls *ls, struct stat fileStat)
{
	ls->buffer[(ls->i)++] = (S_ISDIR(fileStat.st_mode)) ? 'd' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IWUSR) ? 'r' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
}

/*
void    error(t_ls *ls)
{
	free(ls);
	exit(1);
}

*/

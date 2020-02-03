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

// #include <sys/syslimits.h>

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
    a->max_len_time = 0;
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
	a->depth = 0;

	a->info = init_info();
	a->files = NULL;
	return (a);
}



char	*ft_strdup_f(t_ls *ls, const char *src)
{
	char	*s2;
	size_t	i;
	size_t	n;

	n = ft_strlen(src) + 1;
	i = 0;
	if (!(s2 = ft_strnew(n)))
		return (NULL);
	while (src[i] && i < n)
	{
		s2[i] = src[i];
		i++;
	}
	if (ls->F == 1)
		s2[i] = '/';
	return (s2);
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













int     get_size_time(time_t time_)
{
    int		i;
    int     start;

    start = (i = 7);
    if (ABS(difftime(time(NULL), time_)) >= 15768000 && (start = (i = 15)))
        i = 21;
    else
        i = 13;
    return (i - start);
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





t_files     *revive_t_files(t_files **arr)
{
    t_files *start;
    int     i;
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

void        sort_files_t(t_files **arr, int max)
{
    int        i;
    t_files *tmp;

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

void        sort_files_l(t_files **arr, int max)
{
    int        i;
    t_files *tmp;

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

t_files		*sort_files(t_ls *ls, t_files *start, int max)
{
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
		arr[i++] = tmp;
		tmp = tmp->next;
	}
    if (ls->t == 1)
        sort_files_t(arr, max);
    else
        sort_files_l(arr, max);
	start = revive_t_files(arr);
	if (ls->r == 1)
		return(reverse_order_files(start));
	return (start);
}








int         check_args(char *name, t_path **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i]->path, name) == 0)
			return (0);
		i++;
	}
	return (1);
}


size_t      return_time(t_ls *ls, struct stat stats)
{
	if (ls->u == 1)
		return (stats.st_atime);
	return (stats.st_mtime);
}



int         check_permission(struct stat stats)
{
	if (!((stats.st_mode & S_IRUSR) && (stats.st_mode & S_IWUSR)))
		return (1);
	if (!(stats.st_mode & S_IRUSR))
		return (1);
	else if (!((stats.st_mode & S_IRUSR) && (stats.st_mode & S_IWUSR)))
		return (2);
	return (0);
}






void		get_files(t_ls *ls, t_path *curr_d)
{
	DIR             *dir;
	struct dirent   *entry;
	
	t_files			*curr_f;
	t_path			*tmp_d;
	int				tmp;
	int             counter;

	/// Take info about curr. dir
	// printf("\n\tOPEN DIR %s \tDEPTH - %d \n\n", curr_d->path, curr_d->depth);
	if (curr_d->depth == 0)
		curr_d->dir_name = ft_strdup(curr_d->path);
	else
		curr_d->dir_name = ft_strdup(ft_short_name(curr_d->path));
	lstat(curr_d->path, &(curr_d->stats)); // STAT! Not stats!
    /// Read and sort
	dir = opendir(curr_d->path);
	if (!dir)
	{
		if (check_permission(curr_d->stats) == 1)
		{
			ft_putstr(ls->arr[0]->path);
			error(1, curr_d->path);
			return ;
		}
		else if (check_permission(curr_d->stats) == 2)
			return ;
		else
		{
			error(2, curr_d->path);
			return ;
		}

	}
	entry = readdir(dir);
	/// Current dir
	if (ls->a == 1)
	{
        if (curr_d->info->max_len_links < (tmp = ft_strlen(ft_itoa(curr_d->stats.st_nlink))))
            curr_d->info->max_len_links = tmp;
        if (curr_d->info->max_len_owner < (tmp = ft_strlen(getpwuid((uid_t)(curr_d->stats.st_uid))->pw_name)))
            curr_d->info->max_len_owner = tmp;
        if (curr_d->info->max_len_group < (tmp = ft_strlen(getgrgid((gid_t)(curr_d->stats.st_gid))->gr_name)))
            curr_d->info->max_len_group = tmp;
        if (curr_d->info->max_len_size < (tmp = ft_strlen(ft_itoa(curr_d->stats.st_size))))
            curr_d->info->max_len_size = tmp;
        if (curr_d->info->max_len_time < (tmp = get_size_time(return_time(ls, curr_d->stats))))
            curr_d->info->max_len_time = tmp;
		curr_d->files = init_files();
		curr_f = curr_d->files;
		curr_f->filename = ft_strdup_f(ls, ".");
		curr_f->len_name = 1;
		curr_f->stats = curr_d->stats;
	}
	else
		curr_f = curr_d->files;
	tmp = 0;
    counter = 0;
	/// Files
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
            curr_f->filename = ft_strdup_f(ls, ft_short_name(entry->d_name));
            curr_f->len_name = ft_strlen(curr_f->filename);
            lstat(convert_filename(prepare_path(curr_d->path), curr_f->filename), &(curr_f->stats));

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
            if (curr_d->info->max_len_time < (tmp = get_size_time(return_time(ls, curr_f->stats))))
                curr_d->info->max_len_time = tmp;
            counter++;
		}
	}
	if (ls->a == 1)
	    counter++;
	/// Sorting
	if (tmp > 1)
		curr_d->files = sort_files(ls, curr_d->files,counter);
	closedir(dir);

	/// Files


	/// PRINT FILES

    curr_f = curr_d->files;

    if (ls->l == 1)
    {
        curr_d->info->total += curr_d->stats.st_blocks;
        while (curr_f)
        {
            curr_d->info->total += (int)curr_f->stats.st_blocks;
            curr_f = curr_f->next;
        }
        curr_f = curr_d->files;

        if (ls->R == 1 && check_args(curr_d->path, ls->arr))
            show_flag_R(curr_d);

        ft_putstr("total ");
        ft_putstr(ft_itoa(curr_d->info->total));
        ft_putchar('\n');

        while (curr_f)
        {
            put_mode(ls, curr_f->stats, convert_filename(prepare_path(curr_d->path), curr_f->filename)); // Correct
            put_smth(ls, ft_itoa(curr_f->stats.st_nlink), &(curr_d->info->max_len_links), 1); // Put links. Corect.
            //put_smth(ls, getpwuid((uid_t)(curr_f->stats.st_uid))->pw_name, &(curr_d->info->max_len_owner), 1); // Put owner. Correct
            put_owner(ls, getpwuid((uid_t)(curr_f->stats.st_uid))->pw_name, &(curr_d->info->max_len_owner), 1);
            put_owner(ls, getgrgid((gid_t)(curr_f->stats.st_gid))->gr_name, &(curr_d->info->max_len_group), 2);
            // put_smth(ls, getgrgid((gid_t)(curr_f->stats.st_gid))->gr_name, &(curr_d->info->max_len_group), 2); // Put group. Correct
            put_smth(ls, ft_itoa(curr_f->stats.st_size), &(curr_d->info->max_len_size), 2); // Put size. Correct
            put_date(ls, return_time(ls, curr_f->stats)); // Date. Correct
            put_filename(ls, curr_f->filename); // Filename. Correct

	        ls->buffer[(ls->i)] = '\0';
	        ft_putstr(ls->buffer);


			/// Show link
            int     i;
            char    s_tmp[NAME_MAX];
            i = readlink(convert_filename(prepare_path(curr_d->path), curr_f->filename),
                         NULL, 0);
            if (i >= 0)
            {
	            ft_putstr(" -> ");
                readlink(convert_filename(prepare_path(curr_d->path), curr_f->filename),
                         s_tmp, NAME_MAX);
                ft_putstr(s_tmp);
            }

            ft_putchar('\n');
            ls->i = 0;
            curr_f = curr_f->next;
        }
    }
    else
    {
        int max_size;
        int term_size;
        int columns;
        int words;
        int lines;
        char **arr;
        int i;

        if (ls->R == 1)
            show_flag_R(curr_d);
        max_size = curr_d->info->max_len;
        term_size = get_columns();
        words = counter;
        ///Correct
        columns = 1;
        while ((max_size * columns + columns) <= term_size)
            columns++;
        columns--;
        lines = words / columns + ((words % columns > 0) ? 1 : 0);
        //ft_putnbr(lines);
        //ft_putnbr(columns);
        ///


        if (!(arr = malloc(sizeof(char *) * (words + 1))))
            ERROR;
        arr[words] = NULL;
        curr_f = curr_d->files;
        i = 0;
        while (curr_f)
        {
            arr[i++] = curr_f->filename;
            curr_f = curr_f->next;
        }

        int k;
        int shift;
        shift = 0;
        while (shift < lines)
        {
            k = 0;
            while (k < columns && arr[k * lines + shift])
            {
                i = 0;
                while (arr[k * lines + shift] && arr[k * lines + shift][i])
                {
                    ls->buffer[(ls->i)++] = arr[k * lines + shift][i++];
                }
                while (i++ <= max_size)
                    ls->buffer[(ls->i)++] = ' ';
                k++;
            }
            ls->buffer[(ls->i)++] = '\0';
            ft_putstr(ls->buffer);
            ft_putchar('\n');
            ls->i = 0;
            shift++;
        }

    }


	/// END PRINTING


	curr_f = curr_d->files;
	while(curr_f)
	{
        /// Recursive dir
		tmp_d = curr_d;
		if (S_ISDIR(curr_f->stats.st_mode) &&
		ft_strcmp((const char *)curr_f->filename, (const char *)"..") != 0 &&
        ft_strcmp((const char *)curr_f->filename, (const char *)".") != 0 &&
		ls->R == 1)
		{
            ft_putchar('\n');
			curr_d->next = init_path(convert_filename(prepare_path(tmp_d->path), curr_f->filename));
			curr_d->next->depth = tmp_d->depth + 1;
			curr_d->next->info->max_len_size = 0;
			get_files(ls, curr_d->next);
		}
		curr_d = tmp_d;


		curr_f = curr_f->next;
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
	//print_dirs(ls);
	return (0);
}










/*
 * a - invisible files						OK!
 * l - format
 * R - recursive all files in folders		OK!
 * r - sort in reverse order
 * t - sort time
*/



/// CORRECT
char		**check_flags(t_ls *ls, char **av)
{
	if (av[1][0] != '-')
		return (&(av[1]));
	if (!(av[1][1]))
		error(2, (av)[1]);
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
		else if (*((av)[1]) == 'u')
			ls->u = 1;
		else if (*((av)[1]) == 'F')
			ls->F = 1;
		else
			error(3, &(*((av)[1])));
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
	ls->u = 0;
	ls->flags = 0;
	ls->i = 0;
	ls->arr = NULL;
	ls->max_len_time = 12;
	return (ls);
}












void		show_flag_R(t_path *curr_d)
{
	ft_putstr(curr_d->path);
	ft_putstr(":");
	ft_putchar('\n');
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

void	put_filename(t_ls *ls, char *tmp)
{
    ls->buffer[(ls->i)++] = ' ';
    while (*tmp)
        ls->buffer[(ls->i)++] = *(tmp++);
}

void	put_smth(t_ls *ls, char *tmp, int *ls_len, int k)
{
	int		len;
	int		i;

	i = -1;
	ls->buffer[(ls->i)++] = ' ';
	if (k == 2)
        ls->buffer[(ls->i)++] = ' ';
	len = ft_strlen(tmp);
	while (++len <= *ls_len)
		ls->buffer[(ls->i)++] = ' ';
	while (tmp[++i])
		ls->buffer[(ls->i)++] = tmp[i];
}

void    put_owner(t_ls *ls, char *tmp, int *ls_len, int k)
{
    int		i;

    ls->buffer[(ls->i)++] = ' ';
    if (k == 2)
        ls->buffer[(ls->i)++] = ' ';
    i = -1;
    while (tmp[++i])
        ls->buffer[(ls->i)++] = tmp[i];
    while (i++ < *ls_len)
        ls->buffer[(ls->i)++] = ' ';
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
	{
        ls->buffer[(ls->i)++] = ' ';
        while (++i < 20)
            ls->buffer[(ls->i)++] = tmp[i];
    }
	while (++i < 12)
		ls->buffer[(ls->i)++] = tmp[i];
}

void    put_mode(t_ls *ls, struct stat fileStat, char *filename)
{
	char chr;
	acl_t acl;
	acl_entry_t dummy;
	ssize_t xattr;

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

	acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(filename, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		chr = '@';
	else if (acl != NULL)
		chr = '+';
	else
		chr = ' ';
	ls->buffer[(ls->i)++] = chr;
}








void        error(int code, char *file)
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
	}
	else if (code == 3)
	{
		ft_putstr("ls: ");
		ft_putstr("illegal option -- ");
		ft_putchar(*file);
		ft_putchar('\n');
		ft_putstr("usage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n");
	}
	exit(1);
}













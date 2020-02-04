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
	i = -1;
	k = 0;
	while (path[++i])
		if (path[i] == '/' && i > 0)
			k = i + 1;
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
	return (s1);
}



char        *prepare_path(char *s)
{
	char    *s1;
	int     i;
	int     k;
	int     sign;

	i = 0;
	k = 0;
	sign = 0;
	if (!(s1 = ft_strnew(PATH_MAX)))
		ERROR;
	while (s[i])
	{
		if (s[i] != '/' && !(sign = 0))
			s1[k++] = s[i++];
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















size_t      return_time(t_ls *ls, struct stat stats)
{
	if (ls->u == 1)
		return (stats.st_atime);
	return (stats.st_mtime);
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



	if (!(dir = check_dir_and_permission(curr_d)))
		return ;
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
		curr_f->filename = ft_strdup(".");
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
            curr_f->filename = ft_strdup(ft_short_name(entry->d_name));
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
    else if (ls->_1 == 1)
	{
		if (ls->R == 1)
			show_flag_R(curr_d);
		curr_f = curr_d->files;
		while (curr_f)
		{
			ft_putstr(curr_f->filename);
			ft_putstr("\n");
			curr_f = curr_f->next;
		}
	}
    else if (ls->x == 1)
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
	    int i_lines = 0;
	    while (i_lines < lines)
	    {
	    	k = 0;
	    	while (k < columns && arr[i_lines * columns + k])
		    {
			    i = 0;
			    while (arr[i_lines * columns + k][i])
				    ls->buffer[(ls->i)++] = arr[i_lines * columns + k][i++];
			    while (i++ <= max_size)
				    ls->buffer[(ls->i)++] = ' ';
			    k++;
		    }
		    ls->buffer[(ls->i)++] = '\0';
		    ft_putstr(ls->buffer);
		    ft_putchar('\n');
		    ls->i = 0;
	    	i_lines++;
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

		t_files *tmp_f;
		tmp_f = curr_f;
		curr_f = curr_f->next;
		free(tmp_f);
	}
}





void	main_dop(t_ls *ls, int ac, char **av)
{
	int	i;

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
	main_dop(ls, ac, av);
	if (ac == 1)
		get_files(ls, ls->arr[0]);
	else
	{
		i = -1;
		while (ls->arr[++i])
			get_files(ls, (curr = ls->arr[i]));
	}
	exit(0);
}

















void		show_flag_R(t_path *curr_d)
{
	ft_putstr(curr_d->path);
	ft_putstr(":");
	ft_putchar('\n');
}

int		get_columns(void)
{
	struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	// printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);
	return (w.ws_col);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 22:10:32 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/08 22:29:21 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <../libft/includes/libft.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <sys/ioctl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <string.h>
# include <sys/syslimits.h>

# define BUFF_SIZE	1024
# define ERROR		exit

typedef struct	s_info
{
	int				total;
	int				max_len_owner;
	int				max_len_group;
	int				max_len_links;
	int				max_len_size;
	int				max_len;
	int				max_len_time;
}				t_info;

typedef	struct	s_files
{
	char			*filename;
	int				len_name;
	struct s_files	*next;
	struct stat		stats;
}				t_files;

typedef	struct	s_path
{
	struct s_path	*next;
	char			*path;
	char			*dir_name;
	struct stat		stats;
	int				depth;
	t_info			*info;
	t_files			*files;
}				t_path;

typedef struct	s_ls
{
	int				flags;
	int				a;
	int				l;
	int				rr;
	int				r;
	int				t;

	int				u;
	int				one;
	int				x;
	int				s;

	char			buffer[PATH_MAX * 2];
	int				i;
	int				max_len_time;
	struct stat		stats;
	t_path			**arr;
}				t_ls;

int				main(int ac, char **av);

char			**check_flags(t_ls *ls, char **av);

int				get_columns(void);

/*
** ft_sort.c == Не течет
*/

t_files			*revive_files(t_files **arr);
void			sort_files_t(t_files **arr, int max);
void			sort_files_l(t_files **arr, int max);
void			sort_files_s(t_files **arr, int max);
t_files			*sort_files(t_ls *ls, t_files *start, int max);

/*
** ft_reverse.c == Не течет
*/

t_files			*reverse_order_files(t_files *start);

/*
**ft_check_perm.c == Не течет
*/

int				check_permission(struct stat stats);
int				check_permission_for_dir(t_path *curr_d);
DIR				*check_dir_and_permission(t_path *curr_d);
int				check_args(char *name, t_path **arr);

/*
**ft_init.c
*/

t_files			*init_files(void);
t_info			*init_info(void);
t_path			*init_path(char *path);
t_ls			*init_ls(void);
char			**check_flags(t_ls *ls, char **av);

/*
**ft_put.c
*/

void			put_filename(t_ls *ls, char *tmp);
void			put_smth(t_ls *ls, char *tmp, int *ls_len, int k);
void			put_owner(t_ls *ls, char *tmp, int *ls_len, int k);
void			put_date(t_ls *ls, time_t time_);
void			put_mode(t_ls *ls, struct stat filestat, char *filename);

/*
**ft_error.c == Отлично
*/

void			error(int code, char *file);

/*
**ft_convert.c
*/

char			*ft_short_name(char *path);
char			*convert_filename(char *s1, char *s2);
char			*prepare_path(char *s);

/*
**get_term_size.c
*/

void			show_flag_r(t_path *curr_d);
int				get_columns(void);
int				file_hide(char *file);
int				get_size_time(time_t time_);
size_t			return_time(t_ls *ls, struct stat stats);

/*
**ft_check_1.c
*/

t_files			*g_f_check_a(t_ls *ls, t_path *curr_d);
void			g_f_read_files_cheack_stat(t_ls *ls, t_files *curr_f,
t_path *curr_d);
t_files			*g_f_read_files_1(t_files *curr_f, t_path *curr_d);
int				g_f_read_files(t_ls *ls, t_path *curr_d, t_files *curr_f,
DIR *dir);

/*
**ft_get_files.c
*/

void			g_f_rec(t_ls *ls, t_path *curr_d, t_files *curr_f);
void			get_files(t_ls *ls, t_path *curr_d);


void			ft_print_1(t_path *curr_d, t_files *curr_f);
int				*get_col(t_path *curr_d, int *max_size, int *columns);
void			x_dop(int lines, int columns, int max_size, char **arr);
void			ft_print_x(int counter, t_path *curr_d, t_files *curr_f);
void			stand_dop(int lines, int columns, int max_size, char **arr);
void			ft_print_stand(int counter, t_path *curr_d, t_files *curr_f);
void			main_dop(t_ls *ls, int ac, char **av);

/*
**ft_put_dop.c
*/

int				ft_abs(int a);
int				ft_max(int a, int b);
int				len_arr(char **arr);
void			put_flags(t_ls *ls, char **av);

t_ls			*g_ls;

#endif

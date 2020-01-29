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
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <sys/ioctl.h>


# include <../libft/includes/libft.h>

# define BUFF_SIZE 1024

# define ABS(a) (a < 0 ? -a : a)
# define MAX(a, b) (a >= b ? a : b)


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
    blksize_t st_blksize;      размер блока ввода-вывода файловой системы 
    blkcnt_t  st_blocks;       кол-во выделенных блоков по 512Б 
     Начиная с Linux 2.6, ядро поддерживает точность до
       наносекунд в следующих полям меток времени.
       Подробней о версиях до Linux 2.6, смотрите ЗАМЕЧАНИЯ. 
    struct timespec st_atime;   время последнего доступа 
    struct timespec st_mtime;   время последнего изменения 
    struct timespec st_ctime;   время последней смены состояния 
#define st_atime st_atim.tv_sec       для обратной совместимости 
#define st_mtime st_mtim.tv_sec
#define st_ctime st_ctim.tv_sec
};
*/


/*
struct passwd {
    char   *pw_name;        имя пользователя 
    char   *pw_passwd;      пароль пользователя 
    uid_t   pw_uid;         идентификатор пользователя 
    gid_t   pw_gid;         идентификатор группы 
    char   *pw_gecos;       информация о пользователе 
    char   *pw_dir;         домашний каталог 
    char   *pw_shell;       программная оболочка 
};
*/

/*
struct termios {
 tcflag_t c_iflag;  флаги режима ввода 
 tcflag_t c_oflag;  флаги режима вывода 
 tcflag_t c_cflag;  флаги управляющего режима 
 tcflag_t c_lflag;  флаги локального режима 
 cc_t c_line;       дисциплина линии связи 
 cc_t c_cc[NCCS];  управляющие символы 
};
*/



typedef struct	s_dop
{
	int				total; // Это не трогаем
	// Остальное вравниваем через MAX(a, b) и strlen().
	// Параметры для сравнения можно вытаскивать из stats. Подробнее объясню.
	int				max_len_owner;
	int				max_len_group;
	int				max_len_links;
	int				max_len_size;
	int				max_len; // Максимальная длина названий файлов или директорий в текущей директории.
}				t_dop;




// Структура АНИ!

// Тебе понадобится проверка флага ls->r и ls->a
// К этой структуре можно обращаться через структуру t_ls
// Начать с директории ./, т.е. изначально будет next = NULL, filename = ./, deeper = ...
// Очень важно, чтобы filename указывался как ./<название файла иди дир. с полным путем>
// пример: ./src/main.c или ./libft/srcs
typedef	struct	s_files
{
	char			*filename; // Здесь название файла или название директории. Используй malloc.
	char			*short_name; // Название без полного пути. Можно статический массив, т.к. есть ограничение на длину названия файла.
	int				len; // Длина short_name, ft_strlen(short_name).
	struct s_files	*next; // Ссылка на след. название в текущей директории.
	struct s_files	*deeper; // Если это директория, при необходимости уйти вглубь, иначе NULL. Флаг R.

	// После перехода в deeper делаешь malloc структуры t_dop.
	// После перехода в next t_dop ссылаешь на первое создание после перехода в deeper.
	// Туда помещяем максимальные значения.
	t_dop			max_;
}				t_files;


// Структура АРТЕМА!
typedef struct	s_ls
{
	// 0 or 1
	int             flags;
	int             a;
	int             l;
	int             R;
	int             r;
	int             t;

	// Only use to print information
	char            buffer[BUFF_SIZE];
	int             i;

	int				max_len_owner;
	int				max_len_group;
	int				max_len_links;
	int				max_len_size;
	int				max_len_time;

	char            **av;
	char            ac;

	struct stat		stats;

	t_files			files;
}				t_ls;


int             main(int ac, char **av);

void            check_flags(t_ls *ls);
t_ls            *init_ls(int ac, char **av);
void            show_dir(t_ls *ls);

void			put_line_with_l(t_ls *ls, const char *filename);

void            error(t_ls *ls);

void            put_mode(t_ls *ls);
void			put_smth(t_ls *ls, char *tmp, int *ls_len);
void			put_date(t_ls *ls);
void			put_filename(t_ls *ls, const char *filename);

int				get_columns(void);


#endif

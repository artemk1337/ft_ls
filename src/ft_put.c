/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchadwic <cchadwic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 18:28:11 by cchadwic          #+#    #+#             */
/*   Updated: 2020/02/27 18:44:37 by cchadwic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_ls.h"

void		put_smth(t_ls *ls, char *tmp, int *ls_len, int k)
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

void		put_owner(t_ls *ls, char *tmp, int *ls_len, int k)
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

void		put_date(t_ls *ls, time_t time_)
{
	char	*tmp;
	int		i;

	i = -1;
	ls->buffer[(ls->i)++] = ' ';
	tmp = &(ctime(&time_)[4]);
	while (++i < 7)
		ls->buffer[(ls->i)++] = tmp[i];
	i--;
	if (ft_abs(difftime(time(NULL), time_)) >= 15768000 && (i = 15))
	{
		ls->buffer[(ls->i)++] = ' ';
		while (++i < 20)
			ls->buffer[(ls->i)++] = tmp[i];
	}
	while (++i < 12)
		ls->buffer[(ls->i)++] = tmp[i];
}

static void	dop(t_ls *ls, struct stat filestat)
{
	ls->buffer[(ls->i)++] = (S_ISDIR(filestat.st_mode)) ? 'd' : '-';
	ls->buffer[(ls->i)++] = (filestat.st_mode & S_IWUSR) ? 'r' : '-';
	ls->buffer[(ls->i)++] = (filestat.st_mode & S_IWUSR) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (filestat.st_mode & S_IXUSR) ? 'x' : '-';
	ls->buffer[(ls->i)++] = (filestat.st_mode & S_IRGRP) ? 'r' : '-';
	ls->buffer[(ls->i)++] = (filestat.st_mode & S_IWGRP) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (filestat.st_mode & S_IXGRP) ? 'x' : '-';
	ls->buffer[(ls->i)++] = (filestat.st_mode & S_IROTH) ? 'r' : '-';
	ls->buffer[(ls->i)++] = (filestat.st_mode & S_IWOTH) ? 'w' : '-';
	ls->buffer[(ls->i)++] = (filestat.st_mode & S_IXOTH) ? 'x' : '-';
}

void		put_mode(t_ls *ls, struct stat filestat, char *filename)
{
	char		chr;
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;

	dop(ls, filestat);
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

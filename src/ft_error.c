#include "../inc/ft_ls.h"

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
		return ;
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
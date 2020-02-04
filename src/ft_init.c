#include "../inc/ft_ls.h"

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
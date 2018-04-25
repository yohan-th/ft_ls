/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_getinfo.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/29 02:58:46 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/29 02:58:46 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

void		ls_explore(t_lsfields *opts, t_lslist *list_elem)
{
	t_lselem		*elem;
	t_lslist		*list_file;
	DIR				*rep;

	elem = list_elem->first;
	while (elem)
	{
		if (ft_strcmp(elem->name, ".") && ft_strcmp(elem->name, "..") &&
				(rep = opendir(elem->path)))
		{
			if (opts->bgn_print)
				write(1, "\n", 1);
			ft_printf("%s:\n", elem->path);
			list_file = ls_initlist();
			ls_readdir(*opts, elem->path, list_file);
			ls_print(opts, list_file, 0);
			closedir(rep);
		}
		elem = elem->next;
	}
}

/*
** Le strdup dans fillinfo permet de free la liste chainé
*/

void		ls_listfile(char *name, t_lslist *list_file, t_lsfields *opts)
{
	t_lselem	*file_info;

	file_info = ls_fillelem(ft_strdup(name));
	if (!opts->g)
		file_info->color = "\033[m";
	ls_insert(file_info, list_file, opts);
}

void		ls_listfolder(char *name, t_lslist *list_fldr, t_lsfields *opts)
{
	t_lselem	*fldr_info;

	fldr_info = ls_fillelem(ft_strdup(name));
	if (!opts->g)
		fldr_info->color = "\033[m";
	ls_insert(fldr_info, list_fldr, opts);
}

void		ls_readdir(t_lsfields opts, char *name, t_lslist *list_file)
{
	DIR			*rep;
	t_dirent	*files;
	char		*file_path;
	t_lselem	*file_info;

	if (!(rep = opendir(name)))
		ft_printf("ft_ls: %s: Permission denied\n", name);
	else
	{
		while ((files = readdir(rep)) != NULL)
		{
			if (!(!(opts.a) && files->d_name[0] == '.'))
			{
				file_path = ft_strjoin_mltp(3, name, "/", files->d_name);
				file_info = ls_fillelem(file_path);
				if (!opts.g)
					file_info->color = "\033[m";
				ls_insert(file_info, list_file, &opts);
			}
		}
		closedir(rep);
	}
}

void		ls_getinfo(t_lsfields *opts, char *elmt, t_lslist *list_file,
					t_lslist *list_fldr)
{
	t_stat statbuf;

	if (ft_strcmp(elmt, ".") == 0)
		ls_readdir(*opts, ".", list_file);
	else if (stat(elmt, &statbuf) == 0 && S_ISDIR(statbuf.st_mode) == 1)
		ls_listfolder(elmt, list_fldr, opts);
	else
		ls_listfile(elmt, list_file, opts);
}

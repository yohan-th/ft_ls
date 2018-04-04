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

void	ls_listfile(char *name, t_lslist **list_file, t_lsfields *opts)
{
	t_lselem	*file_info;

	file_info = ls_fillinfo(name);
	ls_insert(opts, list_file, file_info);
}

void	ls_listfolder(char *name, t_lslist **list_fldr, t_lsfields *opts)
{
	t_lselem	*fldr_info;

	opts->nb_folders += 1;
	fldr_info = ls_fillinfo(name);
	ls_insert(opts, list_fldr, fldr_info);
}

void	ls_readdir(t_lsfields opts, char *name, t_lslist **list_file)
{
	DIR 		*rep;
	t_dirent	*files;
	char 		*file_path;
	t_lselem	*file_info;

	rep = opendir(name);
	while ((files = readdir(rep)) != NULL)
	{
		if (!(!(opts.a) && files->d_name[0] == '.'))
		{
			file_path = ft_strjoin_mltp(3, name, "/", files->d_name);
			file_info = ls_fillinfo(file_path);
			ls_insert(&opts, list_file, file_info);
		}
	}
	closedir(rep);
}

void	ls_getinfo(t_lsfields *opts, char *elmt, t_lslist **list_file, t_lslist **list_fldr)
{
	if (ft_strcmp(elmt, ".") == 0)
		ls_readdir(*opts, ".", list_file);
	else if (opendir(elmt) == 0)
		ls_listfile(elmt, list_file, opts);
	else
		ls_listfolder(elmt, list_fldr, opts);
}
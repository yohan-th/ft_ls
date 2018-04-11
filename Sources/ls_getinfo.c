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

void	ls_listfile(char *name, t_lslist *list_file, t_lsfields *opts)
{
	t_lselem	*file_info;

	file_info = ls_fillinfo(name);
	ls_insert(file_info, list_file, opts);
}

void	ls_listfolder(char *name, t_lslist *list_fldr, t_lsfields *opts)
{
	t_lselem	*fldr_info;

	opts->nb_folders += 1;
	fldr_info = ls_fillinfo(ft_strdup(name));
	ls_insert(fldr_info, list_fldr, opts);
}

void	ls_readdir(t_lsfields opts, char *name, t_lslist *list_file)
{
	DIR 		*rep;
	t_dirent	*files;
	char 		*file_path;
	t_lselem	*file_info;

	//printf("on ouvre le dossier %s\n", name);
	rep = opendir(name);
	while ((files = readdir(rep)) != NULL)
	{
		//printf("list file %s\n", files->d_name);
		if (!(!(opts.a) && files->d_name[0] == '.'))
		{
			file_path = ft_strjoin_mltp(3, name, "/", files->d_name);
			file_info = ls_fillinfo(file_path);
			ls_insert(file_info, list_file, &opts);
		}
		//printf("**path de file %s\n", file_info->path);
	}
	closedir(rep);
}

void	ls_getinfo(t_lsfields *opts, char *elmt, t_lslist *list_file, t_lslist *list_fldr)
{
	//printf("elmt %s\n", elmt);
	if (ft_strcmp(elmt, ".") == 0)
		ls_readdir(*opts, ".", list_file);
	else if (isDirectory(elmt))
		ls_listfolder(elmt, list_fldr, opts);
	else
		ls_listfile(elmt, list_file, opts);
}

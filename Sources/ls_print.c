/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_print.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/29 20:06:05 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/29 20:06:05 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

void	ls_printclmn(t_lsfields opts, t_lslist *list_elem, t_lsprint print)
{
	t_lselem	*elem;
	int 		file;
	BOOL		found;

	file = 1;
	while (file <= (print.nb_clmn * print.nb_line))
	{
		found = 0;
		elem = list_elem->first;
		while (elem)
		{
			if (elem->pos_clmn == file)
			{
				ft_printf("%s", elem->name);
				ft_putchar_dup(' ', elem->sp_clmn);
				found = 1;
			}
			elem = elem->next;
		}
		if (!found)
			ft_putchar_dup(' ', print.w_clmn);
		if (file % print.nb_clmn == 0)
			ft_printf("\n");
		file++;
	}
}

void	ls_fldr(t_lsfields opts, t_lslist *list_elem)
{
	t_lslist	*list_file;
	t_lselem	*elem;

	elem = list_elem->first;
	while (elem)
	{
		if (opts.nb_folders > 1)
			ft_printf("%s:\n", elem->path);
		list_file = ls_initlist();
		ls_readdir(opts, elem->path, &list_file);
		if (opts.r_lwr && list_file->first)
			ls_revlist(&list_file);
		//printf("on print le dossier %s\n", elem->name);
		//printf("la liste des fichier sont : \n");
		//ls_viewlist(list_file);
		ls_print(opts, list_file, 0);
		elem = elem->next;
	}
}

void	ls_explore(t_lsfields opts, t_lslist *list_elem)
{
	t_lselem	*elem;
	t_lslist	*list_file;

	elem = list_elem->first;
	while (elem)
	{
		//printf("explore folder ? %s\n", elem->path);
		if (opendir(elem->path) != 0)
		{
			//printf("dossier GO\n");
			ft_printf("%s:\n", elem->path);
			list_file = ls_initlist();
			//printf("on rentre dans le dossier %s\n", elem->path);
			ls_readdir(opts, elem->path, &list_file);
			if (opts.r_lwr && list_file->first)
				ls_revlist(&list_file);
			ls_print(opts, list_file, 0);
			//ls_freelist(list_file);
		}
		elem = elem->next;
	}
}

void	ls_print(t_lsfields opts, t_lslist *list_elem, BOOL fldr)
{
	t_lsprint	print;

	if (opts.r_lwr)
		ls_revlist(&list_elem);
	if (fldr)
		ls_fldr(opts, list_elem);
	else if (ls_lenlist(list_elem) > 0)
	{
		//printf("icic\n");
		print = ls_columns(opts, list_elem);
		//printf("rien trille en clmn\n");
		ls_printclmn(opts, list_elem, print);
		printf("\n");
	}
	//free(list_elem);
	//printf("ICI\n");
	if (opts.r_upr && !fldr)
		ls_explore(opts, list_elem);
	//ls_freelist(list_elem);
	//printf("Fin print\n");
	//else

}

//Applications/Slack.app/Contents/Frameworks/Electron Framework.framework/Versions/A/Resources/hi.lproj:
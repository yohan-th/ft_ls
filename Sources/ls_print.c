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

void	ls_printview(t_lsfields opts, t_lslist lst, BOOL foldr)
{
	t_lselem *pelem;
	t_lslist *list_file;

	pelem = lst.first;
	while (pelem)
	{
		if (!foldr)
			ft_printf("%s\n", ls_onlyfile(pelem->name));
		if (foldr && opts.nb_folders > 1)
			ft_printf("%s:\n", pelem->name);
		if (foldr)
		{
			//printf("folder %s\n", pelem->name);
			list_file = ls_initlist();
			ls_readdir(opts, pelem->name, &list_file);
			ls_print(opts, *list_file, 0);
		}
		if (foldr)
			ft_printf("\n");
		pelem = pelem->next;
	}
}

void	ls_printview_r(t_lslist lst, BOOL foldr)
{
	t_lselem *pelem;

	pelem = lst.last;
	while (pelem)
	{
		ft_printf("%s\n", pelem->name);
		pelem = pelem->prev;
	}
}

void	ls_print(t_lsfields opts, t_lslist list_elem, BOOL foldr)
{
	t_lselem *elem;

	if (!opts.r_lwr)
	{
		elem = list_elem.first;
		while (elem)
		{
			ls_printview(opts, list_elem, foldr);
			elem = elem->next;
		}
	}
	else
	{
		elem = list_elem.last;
		while (elem)
		{
			ls_printview(opts, list_elem, foldr);
			elem = elem->prev;
		}
	}
}

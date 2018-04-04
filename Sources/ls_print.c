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
			ft_printf("%s:\n", elem->name);
		list_file = ls_initlist();
		ls_readdir(opts, elem->name, &list_file);
		if (opts.r_lwr && list_file->first)
			ls_revlist(&list_file);
		ls_print(opts, list_file, 0);
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
	else
	{
		print = ls_columns(opts, list_elem);
		ls_printclmn(opts, list_elem, print);
		printf("\n");
	}

	//else

}

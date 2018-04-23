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

void		ls_printclmn(t_lslist *list_elem, t_lsprint print)
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
				ft_printf("%s%s\x1b[0m", elem->color, elem->name);
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

/*
** bgn_print va permettre de sauter une ligne entre chaque
** element sauf au debut & fin
*/

void		ls_fldr(t_lsfields *opts, t_lslist *list_elem)
{
	t_lslist	*list_file;
	t_lselem	*elem;


	elem = list_elem->first;
	while (elem)
	{
		if (ls_lenlist(list_elem) > 1)
		{
			if (opts->bgn_print)
				write(1, "\n", 1);
			ft_printf("%s:\n", elem->path);
		}
		list_file = ls_initlist();
		ls_readdir(*opts, elem->path, list_file);
		ls_print(opts, list_file, 0);
		elem = elem->next;
	}
}

void		ls_explore(t_lsfields *opts, t_lslist *list_elem)
{
	t_lselem	*elem;
	t_lslist	*list_file;
	DIR 		*rep;

	elem = list_elem->first;
	while (elem)
	{
		if ((rep = opendir(elem->path)))
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

void		ls_printlong(t_lsfields *opts, t_lslist *list_elem)
{
	t_lselem	*elem;
	int 		max_nblink;
	int 		max_size;
	int		    max_owner;
	int 		max_group;

	elem = list_elem->first;
	max_nblink = 0;
	max_size = 0;
	max_owner = 0;
	max_group = 0;
	while (elem)
	{
		if (ft_lenint(elem->nb_link) > max_nblink)
			max_nblink = ft_lenint(elem->nb_link);
		if (ft_lenint(elem->size) > max_size)
			max_size = ft_lenint(elem->size);
		if (ft_strlen(elem->owner) > max_owner)
			max_owner = ft_strlen(elem->owner);
		if (ft_strlen(elem->group) > max_group)
			max_group = ft_strlen(elem->group);
		elem = elem->next;
	}
	ft_printf("Total\n");
	elem = list_elem->first;
	while (elem)
	{
		if (ls_lenlist(list_elem) > 1)
		{
			ft_printf("%s%c %*d %-*s  %-*s  %*d %s %s%s\x1b[0m", elem->right, elem->additional_right,
				   max_nblink, elem->nb_link, max_owner, elem->owner, max_group, elem->group,
				   max_size, elem->size, elem->ltime, elem->color, elem->name);
			if (elem->link)
				ft_printf(" -> %s\n", elem->link);
			else
				write(1, "\n", 1);
		}
		elem = elem->next;
	}
}

void		ls_print(t_lsfields *opts, t_lslist *list_elem, BOOL fldr)
{
	t_lsprint	print;

	if (fldr)
		ls_fldr(opts, list_elem);
	else if (ls_lenlist(list_elem) > 0 && opts->l)
	{
		opts->bgn_print = 1;
		ls_printlong(opts, list_elem);
	}
	else if (ls_lenlist(list_elem) > 0)
	{
		opts->bgn_print = 1;
		print = ls_columns(*opts, list_elem);
		ls_printclmn(list_elem, print);
	}
	if (opts->r_upr && !fldr)
		ls_explore(opts, list_elem);
	ls_freelist(list_elem);
}

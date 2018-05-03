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
	int			file;
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
		if (ls_lenlist(list_elem) > 1 || opts->bgn_print)
		{
			if (opts->bgn_print)
				write(1, "\n", 1);
			ft_printf("%s:\n", elem->path);
			opts->bgn_print = 1;
		}
		list_file = ls_initlist();
		ls_readdir(*opts, elem->path, list_file);
		ls_print(opts, list_file, 0);
		elem = elem->next;
	}
}

t_lsprint	ls_spacelong(t_lslist *list_elem, t_lsprint print)
{
	t_lselem	*elem;

	elem = list_elem->first;
	while (elem)
	{
		if (ft_strchr("cb", elem->right[0]))
			elem->size = ft_strjoin_mltp(5, " ", ft_itoa(elem->major), ",",
							ft_chardup(' ', 4 - ft_digitlen(elem->minor)),
							ft_itoa(elem->minor));
		if (ft_lenint(elem->nb_link) > print.sp_nblink)
			print.sp_nblink = ft_lenint(elem->nb_link);
		if (ft_strlen(elem->size) > print.sp_size)
			print.sp_size = ft_strlen(elem->size);
		if (ft_strlen(elem->owner) > print.sp_owner)
			print.sp_owner = ft_strlen(elem->owner);
		if (ft_strlen(elem->group) > print.sp_group)
			print.sp_group = ft_strlen(elem->group);
		print.nb_blocks += elem->st_blocks;
		elem = elem->next;
	}
	return (print);
}

void		ls_printlong(t_lslist *list_elem, t_lsprint print)
{
	t_lselem	*elem;

	if (ls_lenlist(list_elem) > 1)
		ft_printf("total %d\n", print.nb_blocks);
	elem = list_elem->first;
	while (elem)
	{
		if (ls_lenlist(list_elem) >= 1)
		{
			ft_printf("%s%c %*d %-*s  %-*s  %*s %s %s%s\x1b[0m",
						elem->right, elem->additional_right, print.sp_nblink,
						elem->nb_link, print.sp_owner, elem->owner,
						print.sp_group, elem->group, print.sp_size, elem->size,
						elem->ltime, elem->color, elem->name);
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

	ft_bzero(&print, sizeof(t_lsprint));
	if (opts->r_lwr)
		ls_revlist(list_elem);
	if (fldr)
		ls_fldr(opts, list_elem);
	else if (ls_lenlist(list_elem) > 0 && opts->l)
	{
		opts->bgn_print = 1;
		print = ls_spacelong(list_elem, print);
		ls_printlong(list_elem, print);
	}
	else if (ls_lenlist(list_elem) > 0)
	{
		opts->bgn_print = 1;
		print = ls_columns(list_elem);
		ls_printclmn(list_elem, print);
	}
	if (opts->r_upr && !fldr)
		ls_explore(opts, list_elem);
	ls_freelist(list_elem);
}

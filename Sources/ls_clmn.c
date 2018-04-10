/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_clmn.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/04/02 14:42:02 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/04/02 14:42:02 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

int			widthterm(void)
{
	t_winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return ((int)w.ws_col);
}

int			ls_lenclmn(t_lslist *list_elem)
{
	t_lselem	*elem;
	int			len;

	len = 0;
	elem = list_elem->first;
	while (elem)
	{
		if (ft_strlen(elem->name) > (len - 7))
			len = ft_strlen(elem->name) + 7;
		elem = elem->next;
	}
	return (len);
}

/*
** {less_empty} correspond à l'espace libre après avoir rempli
** {len_files} dans {len_array} + marge droite, on le compare pour identifier
** les dimensions parfaites du tableau.
** {len_array} = nb_clmn * w_clmn * nb_line
*/

void		ls_calcclmn(t_lsprint *print)
{
	int len_array;
	int len_files;
	int less_empty;
	int nb_clmn_max;
	int nb_line_tmp;

	nb_clmn_max = print->w_term / print->w_clmn;
	less_empty = print->w_term * print->nb_file;
	while (nb_clmn_max > 0)
	{
		nb_line_tmp = 1;
		len_files = print->w_clmn * print->nb_file;
		len_array = nb_clmn_max * print->w_clmn * 1;
		while (len_files > len_array)
			len_array = nb_clmn_max * print->w_clmn * ++nb_line_tmp;
		if (((print->w_term * nb_line_tmp) - len_files) < less_empty)
		{
			less_empty = (print->w_term * nb_line_tmp) - len_files;
			print->nb_clmn = nb_clmn_max;
			print->nb_line = nb_line_tmp;
		}
		nb_clmn_max -= 1;
	}
}

void		ls_elempos(t_lslist *list_elem, t_lsprint print)
{
	t_lselem	*elem;
	int			line;
	int			clmn;

	line = 0;
	clmn = 1;
	elem = list_elem->first;
	//ls_viewlist(list_elem);

	while (elem)
	{
		//printf("pos de %s\n", elem->path);
		elem->sp_clmn = print.w_clmn - ft_strlen(elem->name);
		elem->pos_clmn = clmn + (line * print.nb_clmn);
		if (++line >= print.nb_line)
		{
			line = 0;
			clmn += 1;
		}
		elem = elem->next;
	}
	//printf("Fin boucle\n");
}

/*
** Par defaut on commence avec 1 colonne à 1 ligne
** {ls_calcclmn} recalculera ces valeurs
*/

t_lsprint	ls_columns(t_lsfields opts, t_lslist *list_elem)
{
	t_lsprint print;

	print.w_term = widthterm();
	print.w_clmn = ls_lenclmn(list_elem);
	print.nb_file = ls_lenlist(list_elem);
	print.nb_clmn = 1;
	print.nb_line = 1;
	ls_calcclmn(&print);
	ls_elempos(list_elem, print);
	return (print);
}

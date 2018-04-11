/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_listinsert.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/27 14:11:03 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/27 14:11:03 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

/*
** On inverse uniquement le pointeur du suivant avec le precedent
** ainsi que le pointeur vers le premier avec le dernier
*/

void	ls_revlist(t_lslist *list)
{
	t_lselem	*t_next;
	t_lselem	*tmp;

	t_next = list->first;
	while (t_next)
	{
		tmp = t_next->next;
		t_next->next = t_next->prev;
		t_next->prev = tmp;
		t_next = t_next->prev;
	}
	tmp = list->first;
	list->first = list->last;
	list->last = tmp;
}

int 	ls_cmp(t_lsfields *opts, t_lselem *elem1, t_lselem *elem2)
{
	char *tmp1;
	char *tmp2;

	//printf("on compare elem1 %s et  %s elem2\n", elem1->name, elem2->name);
	if (opts->t && elem1->time > elem2->time)
		return (1);
	else if (ft_strcmp(elem1->path, elem2->path) <= 0)
		return (1);
	else
		return (0);
}

void	ls_insert(t_lselem *elem, t_lslist *list, t_lsfields *opts)
{
	t_lselem *t_prev;
	t_lselem *t_next;

	//printf("new elem %s\n", elem->name);
	t_prev = NULL;
	t_next = list->first;
	while (t_next && ls_cmp(opts, t_next, elem))
	{
		t_prev = t_next;
		t_next = t_next->next;
	}
	elem->next = t_next;
	elem->prev = t_prev;
	if (t_next)
		t_next->prev = elem;
	if (t_prev)
		t_prev->next = elem;
	if (!elem->prev)
		list->first = elem;
	if (!elem->next)
		list->last = elem;
}

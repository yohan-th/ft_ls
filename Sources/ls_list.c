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

t_lslist	*ls_initlist(void)
{
	t_lslist *list;

	if (!(list = malloc(sizeof(t_lslist))))
		exit(EXIT_FAILURE);
	list->first = NULL;
	list->last = NULL;
	return (list);
}

int			ls_lenlist(t_lslist *list)
{
	t_lselem	*elem;
	int			nb_elem;

	nb_elem = 0;
	elem = list->first;
	while (elem)
	{
		nb_elem += 1;
		elem = elem->next;
	}
	return (nb_elem);
}

/*
** ltime avait été tronqué à +4 donc on revient au debut pour free
*/

void		ls_freelist(t_lslist *list)
{
	t_lselem	*elem;

	elem = list->first;
	while (elem)
	{
		if (elem->prev)
			free(elem->prev);
		if (elem->path)
			free(elem->path);
		free(elem->ltime - 4);
		free(elem->right);
		free(elem->size);
		free(elem->owner);
		free(elem->group);
		if (elem->link)
			free(elem->link);
		if (!elem->next)
		{
			free(elem);
			break ;
		}
		elem = elem->next;
	}
	free(list);
}

int			ls_cmp(t_lsfields *opts, t_lselem *elem1, t_lselem *elem2)
{
	if (opts->t && elem1->time > elem2->time)
		return (1);
	else if (!opts->t && ft_strcmp(elem1->path, elem2->path) <= 0)
		return (1);
	else
		return (0);
}

void		ls_insert(t_lselem *elem, t_lslist *list, t_lsfields *opts)
{
	t_lselem *t_prev;
	t_lselem *t_next;

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

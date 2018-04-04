/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/25 20:46:52 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/25 20:46:53 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef struct	s_elem
{
	int			value;
	struct s_elem	*next;
	struct s_elem	*prev;
}				t_elem;

typedef struct	s_list
{
	t_elem *first;
	t_elem *last;
}				t_list;

void	Insert(t_list **list_infos, int Val)
{
	t_elem *t_prev;
	t_elem *elem;
	t_elem *t_next;

	if (!(elem = malloc(sizeof(t_elem))))
		exit(EXIT_FAILURE);
	t_prev = NULL;
	elem->value = Val;
	t_next = (*list_infos)->first;
	while (t_next && t_next->value < Val)
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
		(*list_infos)->first = elem;
	if (!elem->next)
		(*list_infos)->last = elem;
}

void	Clear(t_list *lst)
{
	t_elem *tmp;
	t_elem *pelem;

	pelem = lst->first;
	while (pelem)
	{
		tmp = pelem;
		pelem = pelem->next;
		free(tmp);
	}
	lst->first = NULL;
	lst->last = NULL;
}

int		Lengths(t_list lst)
{
	int		n;
	t_elem	*pelem;

	n = 0;
	pelem = lst.first;
	while (pelem)
	{
		n++;
		pelem = pelem->next;
	}
	return (n);
}

void	View(t_list lst)
{
	t_elem *pelem;

	pelem = lst.first;
	while (pelem)
	{
		printf("%d\n", pelem->value);
		pelem = pelem->next;
	}
}

void	View_reverse(t_list lst)
{
	t_elem *pelem;

	pelem = lst.last;
	while (pelem)
	{
		printf("%d\n", pelem->value);
		pelem = pelem->prev;
	}
}

int		main(void)
{
	t_list *Mysl;

	Mysl = malloc(sizeof(t_list));
	Mysl->first = NULL;
	Mysl->last = NULL;

	Insert(&Mysl, 1);
	Insert(&Mysl, 8);
	Insert(&Mysl, 0);
	Insert(&Mysl, 5);
	printf("Nb d'elements : %d\n", Lengths(*Mysl));
	View(*Mysl);
	printf("View reverse \n");
	View_reverse(*Mysl);
	Clear(Mysl);
	return (0);
}

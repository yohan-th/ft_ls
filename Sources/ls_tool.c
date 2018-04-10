/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_tool.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/30 00:12:28 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/30 00:12:28 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

/*
** ls_removepath : le while prend un compte le dernier '/' en fin de path
** et le conserve. Ex ~/path/de/mon/fichier/ --> fichier/
*/

char 		*ls_removepath(char *str)
{
	if (!ft_strchr(str, '/') && (ft_strchr(str, '/') + 1) == '\0')
		return (str);
	else
	{
		while (ft_strchr(str, '/') != NULL && ft_strlen(ft_strchr(str, '/')) != 1)
			str = ft_strchr(str, '/') + 1;
		return (str);
	}
}

t_lslist	*ls_initlist(void)
{
	t_lslist *list;

	if (!(list = malloc(sizeof(t_lslist))))
		exit(EXIT_FAILURE);
	list->first = NULL;
	list->last = NULL;
	return (list);
}

void		ls_viewlist(t_lslist *list)
{
	t_lselem	*elem;

	elem = list->first;
	while (elem)
	{
		printf("%s\n", elem->name);
		elem = elem->next;
	}
}

int 		ls_lenlist(t_lslist *list)
{
	t_lselem	*elem;
	int 		nb_elem;

	nb_elem = 0;
	elem = list->first;
	while (elem)
	{
		nb_elem += 1;
		elem = elem->next;
	}
	return (nb_elem);
}

void		ls_freelist(t_lslist *list)
{
	t_lselem	*elem;
	t_lselem	*free_elem;

	elem = list->first;
	while (elem)
	{
		if (elem->prev)
			free(elem->prev);
		if (!elem->next)
			free(elem);
		if (elem->path)
		{
			//printf("free path %s\n", elem->path);
			free(elem->path);
		}
		elem = elem->next;
	}
	free(list);
}

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

char 		*ls_onlyfile(char *str)
{
	if (!ft_strchr(str, '/'))
		return (str);
	else
		return (ft_strchr(str, '/') + 1);
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



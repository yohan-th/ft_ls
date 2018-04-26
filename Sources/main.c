/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/29 12:29:04 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/29 12:29:04 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

/*
** On inverse uniquement le pointeur du suivant avec le precedent
** ainsi que le pointeur vers le premier avec le dernier
** Note : revlist n'a rien a faire dans main.c mais pour respect
** de la norme on ne peut le placer dans list.c
*/

void		ls_revlist(t_lslist *list)
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

void		ls_error(int type, intmax_t c)
{
	if (type == 1)
		ft_printf("ft_ls: illegal option -- %c\n"
			"usage: ls [-GRalrt] [file ...]\n", (char)c);
	else if (type == 2)
		ft_printf("ft_ls: %s: No such file or directory\n", (char *)c);
	else
		ft_printf("ft_ls: Malloc fail\n");
	exit(0);
}

void		ls_checkarg(char *av, t_lsfields *arg)
{
	while (*(++av))
	{
		if (*av == 'l')
			arg->l = 1;
		else if (*av == 'R')
			arg->r_upr = 1;
		else if (*av == 'a')
			arg->a = 1;
		else if (*av == 'r')
			arg->r_lwr = 1;
		else if (*av == 't')
			arg->t = 1;
		else if (*av == 'G')
			arg->g = 1;
		else
			ls_error(1, (intmax_t)*av);
	}
}

t_lsfields	ls_parse(int ac, char ***av)
{
	t_lsfields arg;

	ft_bzero(&arg, sizeof(t_lsfields));
	while (ac > 1 && **av && (**av)[0] == '-')
	{
		if (ft_strlen(**av) >= 2 && (**av)[1] == '-')
		{
			(*av)++;
			break ;
		}
		ls_checkarg(**av, &arg);
		(*av)++;
	}
	return (arg);
}

int			main(int ac, char **av)
{
	t_lsfields	opts;
	t_lslist	*list_file;
	t_lslist	*list_fldr;

	av++;
	opts = ls_parse(ac, &av);
	list_file = ls_initlist();
	list_fldr = ls_initlist();
	if (*av == 0)
		ls_getinfo(&opts, ".", list_file, list_fldr);
	else
	{
		while (*av)
			ls_getinfo(&opts, *av++, list_file, list_fldr);
	}
	if (list_file->first)
		ls_print(&opts, list_file, 0);
	else
		free(list_file);
	if (list_fldr->first)
	{
		printf("folder\n");
		ls_print(&opts, list_fldr, 1);
	}
	else
		free(list_fldr);
	return (1);
}

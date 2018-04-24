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

void		ls_error(char c)
{
	if (c < 0)
		ft_printf("--> Error code %d\n", c);
	else
		ft_printf("ft_ls: illegal option -- %c\n"
			"usage: ls [-GRalrt] [file ...]\n", c);
	exit(0);
}

void 	ls_checkarg(char *av, t_lsfields *arg)
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
			ls_error(*av);
	}
}

t_lsfields	ls_parse(int ac, char ***av)
{
	t_lsfields arg;

	ft_bzero(&arg, sizeof(t_lsfields));
	while (ac > 1 && **av && (*av)[0][0] == '-')
	{
		ls_checkarg(**av, &arg);
		(*av)++;
	}
	return (arg);
}

int 		main(int ac, char **av)
{
	t_lsfields	opts;
	t_lslist *list_file;
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
	if (list_fldr->first)
		ls_print(&opts, list_fldr, 1);
    return (1);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   test.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/21 23:42:32 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/21 23:42:34 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

t_fields_ls	ft_parse_ls(char *arg)
{

}
int 		main(int ac, char **av)
{
	t_fields_ls arg;
	if (ac == 1) //Pas d'argument, dossier courent
	{
		printf("ICI\n");
		ft_list_dir(".", 1);
	}
	else if (ac > 1)
	{
		ft_pa
	}
		printf("%d\n", ac);

    return (1);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_list_dir.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/21 21:32:44 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/21 21:32:47 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

int ft_list_dir(char *folder, BOOL all)
{
    DIR* rep = NULL;
    struct dirent* files = NULL;

    if (!(rep = opendir(folder)))
        return (0);
    files = readdir(rep);
    while ((files = readdir(rep)) != NULL)
	{
		if (!(!(all) && files->d_name[0] == '.'))
			ft_printf("Le fichier lu s'appelle %s\n", files->d_name);
	}

    closedir(rep);
    return (1);
}

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

void	ls_error(char c)
{
	ft_printf("ft_ls: illegal option -- %c\n"
			"usage: ls [-Ralrt] [file ...]\n", c);
	exit(0);
}


t_lsfields	ls_parse(char *av)
{
	t_lsfields arg;

	av++;
	while (*av)
	{
		if (*av == 'l')
			arg.l = 1;
		else if (*av == 'R')
			arg.r_upr = 1;
		else if (*av == 'a')
			arg.a = 1;
		else if (*av == 'r')
			arg.r_lwr = 1;
		else if (*av == 't')
			arg.t = 1;
		else
			ls_error(*av);
		av++;
	}
	return (arg);
}


char	*ft_strjoin_multiple(int n, ...)
{
	va_list	ap;
	char	*tmp;
	char	*cpy;
	char	*full;

	full = ft_strdup("");
	va_start(ap, n);
	while (n--)
	{
		tmp = va_arg(ap, char *);
		if (!tmp)
			break ;
		cpy = full;
		full = ft_strjoin(cpy, tmp);
		free(cpy);
	}
	va_end(ap);
	return (full);
}

//Rempli la liste chainé {**list} avec le(s) element(s) du nom de {*elmt}
void	ls_getinfo(t_lsfields opts, char *elmt, t_lslist **list)
{
	t_lselem	*file_info;
	DIR* 		rep;
	t_dirent	*files;
	char 		*file_path;

	if (opendir(elmt) == 0) // si fichier
	{
		file_info = ls_fillinfo(elmt);
		ls_insert(opts, list, file_info);
	}
	else if ((rep = opendir(elmt)))
	{
		while ((files = readdir(rep)) != NULL)
		{
			printf("file %s\n", files->d_name);
			if (!(!(opts.a) && files->d_name[0] == '.'))
			{
				printf("ICI\n");
				//file_path = ft_strcat_free()
				file_info = ls_fillinfo(files->d_name);
				printf("La\n");
				printf("file name %s\n", file_info->name);
				ls_insert(opts, list, file_info);
			}
		}
		closedir(rep);
	}
	//printf("<%p>\n", elmt);
}

int 		main(int ac, char **av)
{
	t_lsfields opts = {0};
	t_lslist *list;

	av++;
	if (ac > 1 && av[0][0] == '-')
	{
		opts = ls_parse(av[0]);
		av++;
	}
	if (!(list = malloc(sizeof(t_lslist))))
		exit(EXIT_FAILURE);
	list->first = NULL;
	list->last = NULL;
	if (*av == 0)
		ls_getinfo(opts, ".", &list);
	else
	{
		while (*av)
			ls_getinfo(opts, *av++, &list);
	}
	printf("FIN\n");

    return (1);
}

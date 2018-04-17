/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ls_fillelem.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/28 17:03:09 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/28 17:03:09 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

/*
** time[16] = '\0'; permet de tronquer la date initialement
** "Mon Mar 19 12:25:59 2018"
** puis on ajoute +4 à time pour avancer et tronquer "Mon "
*/

char		*ft_def_elmt(int elmt)
{
	if (elmt == 16877)
		return ("Folder");
	else if (elmt == 33188)
		return ("File");
	ft_printf("object not determinate : %d\n", elmt);
	return (0);
}

char		*ft_def_right(t_stat s)
{
	char *rights;

	rights = (char *)malloc(sizeof(char) * 11);
	rights[0] = (S_ISDIR(s.st_mode)) ? (char)'d' : (char)'-';
	rights[1] = (s.st_mode & S_IRUSR) ? (char)'r' : (char)'-';
	rights[2] = (s.st_mode & S_IWUSR) ? (char)'w' : (char)'-';
	rights[3] = (s.st_mode & S_IXUSR) ? (char)'x' : (char)'-';
	rights[4] = (s.st_mode & S_IRGRP) ? (char)'r' : (char)'-';
	rights[5] = (s.st_mode & S_IWGRP) ? (char)'w' : (char)'-';
	rights[6] = (s.st_mode & S_IXGRP) ? (char)'x' : (char)'-';
	rights[7] = (s.st_mode & S_IROTH) ? (char)'r' : (char)'-';
	rights[8] = (s.st_mode & S_IWOTH) ? (char)'w' : (char)'-';
	rights[9] = (s.st_mode & S_IXOTH) ? (char)'x' : (char)'-';
	rights[10] = '\0';
	return (rights);
}

char		*ls_getcolor(mode_t st_mode)
{
	if (S_ISFIFO(st_mode))
		return ("\033[0;33;40m");
	else if (S_ISCHR(st_mode))
		return ("\033[0;34;43m");
	else if (S_ISDIR(st_mode))
		return ("\033[1;36m");
	else if (S_ISBLK(st_mode))
		return ("\033[0;34;46m");
	else if (S_ISREG(st_mode))
		return ("\033[m");
	else if (S_ISLNK(st_mode))
		return ("\033[0;35m");
	else if (S_ISSOCK(st_mode))
		return ("\033[0;32m");
	else //is exec
		return ("\033[0;31m");
	return ("\033[1;36;40m");
}

t_lselem	*ls_fillelem(char *elmt)
{
	t_stat		s;
	t_passwd	*pw;
	t_group		*gr;
	t_lselem	*infos;
	char		*tmp;

	if (!(infos = malloc(sizeof(t_lselem))) || (lstat(elmt, &s)) == -1)
		ls_error(-1);
	infos->path = elmt;
	infos->name = ls_removepath(elmt);
	infos->color = ls_getcolor(s.st_mode);
	infos->right = ft_def_right(s);
	infos->size = (int)s.st_size;
	infos->nb_link = s.st_nlink;
	infos->owner = getpwuid(s.st_uid)->pw_name;
	infos->group = getgrgid(s.st_gid)->gr_name;
	infos->time = (int)s.st_mtime;
	return (infos);
}

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

char		*ls_def_typeORcolor(mode_t st_mode, char *def)
{
	if (S_ISFIFO(st_mode))
		return (ft_strcmp(def, "type") == 0 ? "p" : "\033[0;33;40m");
	else if (S_ISCHR(st_mode))
		return (ft_strcmp(def, "type") == 0 ? "c" : "\033[0;34;43m");
	else if (S_ISDIR(st_mode))
		 return (ft_strcmp(def, "type") == 0 ? "d" : "\033[1;36m");
	else if (S_ISBLK(st_mode))
		return (ft_strcmp(def, "type") == 0 ? "b" : "\033[0;34;46m");
	else if (S_ISREG(st_mode))
		return (ft_strcmp(def, "type") == 0 ? "-" : "\033[m");
	else if (S_ISLNK(st_mode))
		return (ft_strcmp(def, "type") == 0 ? "l" : "\033[0;35m");
	else if (S_ISSOCK(st_mode))
		return (ft_strcmp(def, "type") == 0 ? "s" : "\033[0;32m");
	else if (ft_strcmp(def, "type") == 0)
		return ("d");
	else if (ft_strcmp(def, "color") == 0)
		return ("\033[1;36;40m");
	return (NULL);
	//return ("\033[0;31m"); if exec
}

char		*ls_def_right(t_stat s)
{
	char *rights;

	rights = (char *)malloc(sizeof(char) * 11);
	rights[0] = ls_def_typeORcolor(s.st_mode, "type")[0];
	rights[1] = (s.st_mode & S_IRUSR) ? (char)'r' : (char)'-';
	rights[2] = (s.st_mode & S_IWUSR) ? (char)'w' : (char)'-';
	rights[3] = (s.st_mode & S_IXUSR) ? (char)'x' : (char)'-';
	rights[3] = (s.st_mode & S_ISUID && s.st_mode & S_IXUSR) ? 's' : rights[3];
	rights[3] = (s.st_mode & S_ISUID && rights[3] == '-') ? 'S' : rights[3];
	rights[4] = (s.st_mode & S_IRGRP) ? (char)'r' : (char)'-';
	rights[5] = (s.st_mode & S_IWGRP) ? (char)'w' : (char)'-';
	rights[6] = (s.st_mode & S_IXGRP) ? (char)'x' : (char)'-';
	rights[6] = (s.st_mode & S_ISGID && s.st_mode & S_IXGRP) ? 's' : rights[6];
	rights[6] = (s.st_mode & S_ISGID && rights[6] == '-') ? 'S' : rights[6];
	rights[7] = (s.st_mode & S_IROTH) ? (char)'r' : (char)'-';
	rights[8] = (s.st_mode & S_IWOTH) ? (char)'w' : (char)'-';
	rights[9] = (s.st_mode & S_IXOTH) ? (char)'x' : (char)'-';
	rights[9] = (s.st_mode & S_ISVTX && s.st_mode & S_IXOTH) ? 't' : rights[9];
	rights[9] = (s.st_mode & S_ISVTX && rights[9] == '-') ? 'T' : rights[9];
	rights[10] = '\0';
	return (rights);
}

/*
** 
*/

char        ls_additional_right(char *path)
{
	acl_t acl;

	if ((listxattr(path, NULL, 1, XATTR_NOFOLLOW)) > 0)
		return ('@');
	else if ((acl = acl_get_file(path, ACL_TYPE_EXTENDED)))
	{
		acl_free(acl);
		return ('+');
	}
	else
		return (' ');
}

/*
** Si la derniere modif est +6 mois environs on affiche l'année.
** ltime[16] = '\0' permet de tronquer la date :
** "Mon Mar 19 12:25{+\0}:59 2018"
** puis on ajoute +4 à time pour avancer et tronquer "Mon "
*/

char        *ls_time(t_stat s)
{
	char *ltime;

	ltime = ft_strdup(ctime(&s.st_mtime));
	if (s.st_mtime < (time(NULL) - 60*60*24*30*6))
	{
		ltime[11] = ' ';
		ltime[12] = ltime[20];
		ltime[13] = ltime[21];
		ltime[14] = ltime[22];
		ltime[15] = ltime[23];
		ltime[16] = '\0';
	}
	else
		ltime[16] = '\0';
	return(ltime + 4);
}

t_lselem	*ls_fillelem(char *elmt)
{
	t_stat	    s;
	t_lselem   *infos;
    char          *buf;

	if (!(infos = malloc(sizeof(t_lselem))) || (lstat(elmt, &s)) == -1)
		ls_error(-1);
	infos->path = elmt;
	infos->name = ls_removepath(elmt);
	infos->color = ls_def_typeORcolor(s.st_mode, "color");
	infos->right = ls_def_right(s);
	infos->additional_right = ls_additional_right(elmt);
	infos->size = (int)s.st_size;
	infos->nb_link = s.st_nlink;
	infos->owner = getpwuid(s.st_uid)->pw_name;
	infos->group = getgrgid(s.st_gid)->gr_name;
	infos->time = (int)s.st_mtime;
	infos->ltime = ls_time(s);
	buf = ft_strnew(1024);
	if (S_ISLNK(s.st_mode) && readlink(infos->path, buf, 1024) != -1)
	    infos->link = buf;
	else
	    infos->link = NULL;
	return (infos);
}

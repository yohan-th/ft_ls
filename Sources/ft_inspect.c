/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_inspect.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/21 23:15:58 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/21 23:16:00 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Include/ft_ls.h"

/*
** time[16] = '\0'; permet de tronquer la date initialement "Mon Mar 19 12:25:59 2018"
** puis on ajoute +4 à time pour avancer et tronquer "Mon "
*/

char    *ft_def_elmt(int elmt)
{
    if (elmt == 16877)
        return ("Folder");
    else if (elmt == 33188)
        return ("File");
    ft_printf("object not determinate : %d\n", elmt);
    return (0);
}

char	*ft_def_right(struct stat s)
{
    char *rights;

    rights = (char *)malloc(sizeof(char) * 11);
    rights[0] = (S_ISDIR(s.st_mode)) ? 'd' : '-';
    rights[1] = (s.st_mode & S_IRUSR) ? 'r' : '-';
    rights[2] = (s.st_mode & S_IWUSR) ? 'w' : '-';
    rights[3] = (s.st_mode & S_IXUSR) ? 'x' : '-';
    rights[4] = (s.st_mode & S_IRGRP) ? 'r' : '-';
    rights[5] = (s.st_mode & S_IWGRP) ? 'w' : '-';
    rights[6] = (s.st_mode & S_IXGRP) ? 'x' : '-';
    rights[7] = (s.st_mode & S_IROTH) ? 'r' : '-';
    rights[8] = (s.st_mode & S_IWOTH) ? 'w' : '-';
    rights[9] = (s.st_mode & S_IXOTH) ? 'x' : '-';
    rights[10] = '\0';
    return (rights);
}

int     ft_inspect(char *elmt)
{
    t_stat      s;
    t_passwd    *pw;
    t_group     *gr;
    char        *tmp;

    if((stat(elmt,&s)) == -1)
        return (ft_printf("Not found\n"));
    ft_printf("Name:\t\t%s\n",elmt);
    ft_printf("Type:\t\t%s\n", ft_def_elmt(s.st_mode));
    ft_printf("Modes:\t\t%s\n", (tmp = ft_def_right(s)));
    free(tmp);
    ft_printf("taille:\t\t%lld octets\n",s.st_size);
    ft_printf("Lien:\t\t%hu\n", s.st_nlink);
    pw = getpwuid(s.st_uid);
    ft_printf("Proprio:\t%s\n", pw->pw_name);
    gr = getgrgid(s.st_gid);
    ft_printf("Group:\t\t%s\n", gr->gr_name);
    ft_printf("Size:\t\t%lld octets\n", s.st_size);
    tmp = ctime(&s.st_mtime);
    tmp[16] = '\0';
    ft_printf("last modif:\t%s\n", tmp + 4);
	return (1);
}

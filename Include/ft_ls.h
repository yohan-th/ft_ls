/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <ythollet@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/29 12:28:35 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/29 12:28:35 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_LS_H

# define FT_LS_H
# include <stdlib.h>
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>

# include "../Libft/Includes/libft.h"

typedef struct stat		t_stat;
typedef struct group	t_group;
typedef struct passwd	t_passwd;
typedef struct dirent	t_dirent;

typedef struct	s_lsfields
{
	BOOL	r_upr;
	BOOL	a;
	BOOL	l;
	BOOL	r_lwr;
	BOOL	t;
	int		nb_folders;
	int 	nb_files;
}				t_lsfields;

typedef struct  s_lselem
{
	int				time;
	char			*name;
	struct s_lselem *next;
	struct s_lselem *prev;
}				t_lselem;

typedef struct	s_lslist
{
	t_lselem *first;
	t_lselem *last;
}				t_lslist;

t_lselem		*ls_fillinfo(char *elmt);
int				ls_list_dir(char *folder, BOOL all);
void			ls_insert(t_lsfields *opts, t_lslist **list_infos, t_lselem *elem);
void			ls_getinfo(t_lsfields *opts, char *elmt, t_lslist **list_file, t_lslist **list_fldr);
void			ls_readdir(t_lsfields opts, char *name, t_lslist **list_file);
void			ls_print(t_lsfields opts, t_lslist list_elem, BOOL fldr);
char 			*ls_onlyfile(char *str);
t_lslist		*ls_initlist(void);

#endif

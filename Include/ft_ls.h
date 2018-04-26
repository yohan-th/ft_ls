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
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <sys/ioctl.h>
# include <stdio.h>

# include "../Libft/Includes/libft.h"

typedef struct stat		t_stat;
typedef struct dirent		t_dirent;
typedef struct winsize		t_winsize;

typedef struct				s_lsfields
{
	BOOL	r_upr;
	BOOL	a;
	BOOL	l;
	BOOL	r_lwr;
	BOOL	t;
	BOOL	g;
	BOOL	bgn_print;
}							t_lsfields;

typedef struct				s_lslist
{
	struct s_lselem		*first;
	struct s_lselem		*last;
}							t_lslist;

/*
** size est une chaine de caractere de chiffre car contiendra
*/

typedef struct				s_lselem
{
	int					time;
	char				*ltime;
	char				*name;
	char				*path;
	char				*color;
	char				*right;
	char				additional_right;
	int					nb_link;
	char				*owner;
	char				*group;
	char				*link;
	char				*size;
	int					major;
	int					minor;
	int					st_blocks;
	int					pos_clmn;
	int					sp_clmn;
	struct s_lselem		*next;
	struct s_lselem		*prev;
}							t_lselem;

typedef struct				s_lsprint
{
	int	w_term;
	int	w_clmn;
	int	nb_file;
	int	nb_clmn;
	int	nb_line;
	int	sp_nblink;
	int	sp_size;
	int	sp_owner;
	int	sp_group;
	int	nb_blocks;
}							t_lsprint;

t_lselem					*ls_fillelem(char *elmt);
void						ls_insert(t_lselem *elem, t_lslist *list,
									t_lsfields *opts);
void						ls_getinfo(t_lsfields *opts, char *elmt,
									t_lslist *list_file, t_lslist *list_fldr);
void						ls_readdir(t_lsfields opts, char *name,
									t_lslist *list_file);
void						ls_print(t_lsfields *opts, t_lslist *list_elem,
									BOOL fldr);
t_lsprint					ls_columns(t_lslist *list_elem);
void						ls_explore(t_lsfields *opts, t_lslist *list_elem);
t_lslist					*ls_initlist(void);
int							ls_lenlist(t_lslist *list);
void						ls_error(int type, intmax_t c);
void						ls_freelist(t_lslist *list);
void						ls_revlist(t_lslist *list);

#endif

/*
** Hard test
** /Volumes/Mac OS/Volumes/Storage/cache/ythollet/Library/Logs/DiagnosticReports
** /private/var/db/mds/messages
** file & folder no right
*/

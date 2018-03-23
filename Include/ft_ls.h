/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_ls.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: ythollet <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/03/23 16:44:33 by ythollet     #+#   ##    ##    #+#       */
/*   Updated: 2018/03/23 16:44:36 by ythollet    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "../Libft/Includes/libft.h"

typedef struct stat     t_stat;
typedef struct group	t_group;
typedef struct passwd	t_passwd;

typedef struct	s_fields_ls
{
	BOOL	l;
	BOOL	r_upr;
	BOOL	a;
	BOOL	r_lwr;
	BOOL	t;
}				t_fields_ls;


int     ft_inspect(char *elmt);
int 	ft_list_dir(char *folder, BOOL all);

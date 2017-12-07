/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 11:33:52 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/12 16:13:46 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include <sys/ioctl.h>
# include "libft.h"
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <stdlib.h>
# include <dirent.h>
# include "ft_select.h"

# define MODE COLUMN
# define COLUMN 1
# define LINE 2
# define BUFF_SIZE 1024

typedef struct	s_elem
{
	char			*name;
	int				size;
	int				selected;
	struct s_elem	*prev;
	struct s_elem	*next;
}				t_elem;

typedef struct	s_selectdata
{
	struct termios	term;
	t_elem			*cursor;
	t_elem			*list;
	char			*buff;
	int				fd;
	int				colsize;
	int				nbcols;
	int				nbelems;
}				t_selectdata;

t_selectdata *g_ftselect;

int				custom_putchar(int c);
void			putselecteds(t_elem *list);
void			freelist(t_elem *list);
t_elem			*ft_mklist(int argc, char **argv);
t_elem			*ft_mkselecteds(t_elem *list);
int				inits(t_elem *list);
char			*ft_select(t_elem *list);
int				showlist(t_elem *list);
void			cleanterm(void);
int				keyhooks(void);
void			mvtop(void);
void			mvbot(void);
void			mvleft(void);
void			mvright(void);
void			deinit(void);
void			setselectsignal(void);
void			setallsignal(void);
void			selecthandler(int signal);
void			ft_elem_lstdel(t_elem **alst);
#endif

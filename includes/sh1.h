/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh1.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/22 02:00:31 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/15 16:52:04 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH1_H
# define SH1_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <sys/signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/uio.h>
# include "libft.h"
# include <sys/ioctl.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <stdio.h>
# include "ft_select.h"

# define MAX_FD 20

int				g_ttyfd;
char			*g_buff;

typedef struct	s_execdata
{
	char		**env;
	char		**av;
	int			fd[MAX_FD];
}				t_execdata;

typedef struct	s_history
{
	char		**history;
	int			current;
	int			size;
	int			fd;
}				t_history;

int				custom_putchar(int c);
int				showprompt(char *currentdir);
int				showstringtab(char **strtab);
char			**ft_tabstrdup(char **thetab);
int				execbi(char *str, t_execdata *data);
int				ft_env(t_execdata *data);
int				ft_deinit(t_execdata *data, t_history *history);
int				ft_setenv(t_execdata *data, const char *name,
						const char *value, int overwrite);
int				ft_unsetenv(t_execdata *data, const char *name);
char			*ft_getenv(char **env, char *elem);
int				ft_cd(t_execdata *data);
int				childexec(t_execdata *data, t_execdata *tmp);
void			ft_welcome(void);
void			ft_goodbye(void);
void			setallsignal(void);
void			unsetallsignal(void);
void			handler(int signal);
void			unhandler(int signal);
int				pipedcommands(char *buff, t_execdata *child);
int				launchprogram(t_execdata *data, t_execdata *tmp);
int				getinputs(char *buff, t_history *history);
int				init(char **buff, t_execdata **child, char **env,
					t_history **history);
void			mvcursor(char *buff, char **ptr, t_history *history);
void			mvcright(int size);
void			mvcleft(int size);
void			mvctop(void);
void			mvcbot(void);
void			mvcstart(char *buff, char **ptr);
void			mvcend(char **ptr);
void			mvclineup(char *buff, char **ptr);
void			mvclinedown(char *buff, char **ptr);
void			completion(char *buff, char **ptr);
int				add_str_to_tab(char ***strtab, const char *str);
void			copycutpaste(char input, char *buff, char **ptr);
int				in_from_stdin(t_execdata *data, char ***avptra);
int				in_from_file(t_execdata *data, char ***avptra);
int				out_to_file(t_execdata *data, char ***avptra, int append);

#endif

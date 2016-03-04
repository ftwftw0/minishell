/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 18:56:47 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/04 15:42:00 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static int		terminit(void)
{
	struct termios	term;
	char			*termname;

	if (!(termname = getenv("TERM")))
	{
		if ((tgetent(NULL, "xterm-256color") == -1) ||
			(tcgetattr(0, &(term)) == -1))
			return (-1);
	}
	else if (tgetent(NULL, termname) == -1 ||
			 (g_ttyfd = open("/dev/tty", O_RDWR)) == -1 ||
			 tcgetattr(g_ttyfd, &term) == -1)
	{
		perror("tcgetattr");
		return (-1);
	}
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(g_ttyfd, TCSANOW, &(term)) == -1)
	{
		ft_putendl_fd("Can't initialize terminal infos", 2);
		return (-1);
	}
	return (1);
}

static int		loadhistory(t_history *history, char **env)
{
	char	*home;
	char	*tmp;

	history->history = (char **)malloc(sizeof(char *) * 1);
	history->size = 0;
	history->history[0] = NULL;
	if (!env || !(env[0]) || !(home = ft_getenv(env, "HOME")) ||
		!(tmp = ft_strjoin(home, "/.myshhistory")) ||
		(history->fd = open(tmp, O_CREAT | O_RDWR | O_APPEND, 0644)) == -1)
	{
		perror("cannot load command history file");
		history->fd = 0;
		return (0);
	}
	free(home);
	free(tmp);
	tmp = NULL;
	while (get_next_line(history->fd, &tmp) >= 0)
	{
	  if (tmp && tmp[0] && tmp[0] != '\n')
	    {
	      add_str_to_tab(&(history->history), tmp);
		free(tmp);
		tmp = NULL;
		history->size++;
	    }
	}
	return (1);
}

int				init(char **buff, t_execdata **child, char **env, t_history **history)
{
	if (((*buff) = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)) == NULL)
		return (-1);
	if (((*history) = (t_history *)malloc(sizeof(t_history))) == NULL ||
		loadhistory(*history, env) == -1)
		return (-1);
	(*history)->current = ft_tablen((*history)->history);
	if (((*child) = (t_execdata *)malloc(sizeof(t_execdata))) == NULL)
		return (-1);
	(*child)->env = ft_tabstrdup(env);
	set_righthome((*child));
	(*child)->fd[0] = 0;
	(*child)->fd[1] = 1;
	(*child)->av = NULL;
	if (terminit() == -1)
		return (-1);
	setallsignal();
	return (1);
}

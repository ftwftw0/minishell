/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 18:36:00 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/23 02:31:45 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	deinit_norm(t_history *history)
{
	if (history)
	{
		ft_freetab(&(history->history));
		close(history->fd);
	}
	close(g_ttyfd);
	free(g_buff);
}

int			ft_deinit(t_execdata *data, t_history *history)
{
	struct termios	term;
	char			*termname;

	if (data != NULL)
	{
		ft_freetab(&(data->av));
		ft_freetab(&(data->env));
		free(data);
	}
	if (!(termname = getenv("TERM")))
		termname = ft_strdup("xterm-256color");
	if ((tgetent(NULL, termname) == -1) ||
		(tcgetattr(g_ttyfd, &(term)) == -1))
		return (-1);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(g_ttyfd, TCSADRAIN, &(term)) == -1)
	{
		ft_putendl_fd("Can't initialize terminal infos", 2);
		return (-1);
	}
	deinit_norm(history);
	return (1);
}

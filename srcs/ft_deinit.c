/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 18:36:00 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/15 11:43:42 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int ft_deinit(t_execdata *data)
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
	if ((tgetent(0, termname) == -1) ||
		(tcgetattr(0, &(term)) == -1))
		return (-1);
	term.c_lflag |= ICANON;
	term.c_lflag |= ECHO;
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &(term)) == -1)
	{
		ft_putendl_fd("Can't initialize terminal infos", 2);
		return (-1);
	}
	return (1);
}

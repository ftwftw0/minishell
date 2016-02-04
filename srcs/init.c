/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 18:56:47 by flagoutt          #+#    #+#             */
/*   Updated: 2016/02/04 06:43:42 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static int		terminit(void)
{
	struct termios	term;
	char			*termname;

	if (!(termname = getenv("TERM")))
	{
		if ((tgetent(0, "xterm-256color") == -1) ||
			(tcgetattr(0, &(term)) == -1))
			return (-1);
	}
	else if ((tgetent(0, termname) == -1) ||
			(tcgetattr(0, &(term)) == -1))
		return (-1);
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &(term)) == -1)
	{
		ft_putendl_fd("Can't initialize terminal infos", 2);
		return (-1);
	}
	return (1);
}

int				init(char **buff, t_execdata **child, char **env)
{
	if (((*buff) = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)) == NULL)
		return (0);
	if (((*child) = (t_execdata *)malloc(sizeof(t_execdata))) == NULL)
		return (0);
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

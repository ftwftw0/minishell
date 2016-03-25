/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 17:00:39 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/25 13:58:56 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <stdio.h>

int			launchcommands(char *buff, t_execdata *child)
{
	char		**commands;
	int			i;

	commands = ft_strsplit(buff, ';');
	i = -1;
	while (commands[++i])
	{
		if (pipedcommands(commands[i], child) == 0)
		{
			ft_freetab(&commands);
			return (0);
		}
	}
	ft_freetab(&commands);
	return (1);
}

static void	checkcanonmode(void)
{
	struct termios	term;
	char			*termname;

	if (!(termname = getenv("TERM")))
	{
		if ((tgetent(0, "xterm-256color") == -1) ||
			(tcgetattr(0, &(term)) == -1))
			return ;
	}
	else if ((tgetent(0, termname) == -1) || (tcgetattr(0, &(term)) == -1))
		return ;
	if (term.c_cc[VMIN] == 1)
		return ;
	term.c_lflag &= ~(ICANON | ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &(term)) == -1)
		ft_putendl_fd("Can't initialize terminal infos", 2);
}

int			main(int argc, char **argv, char **env)
{
	t_history	*history;
	t_execdata	*child;

	if (init(&g_buff, &child, env, &history) == -1)
		return (-1);
	(void)argc;
	(void)argv;
	if (isatty(0))
		ft_welcome();
	while (1)
	{
		checkcanonmode();
		getcwd(g_buff, BUFF_SIZE);
		showprompt(g_buff);
		ft_bzero(g_buff, BUFF_SIZE);
		if ((getinputs(g_buff, history) == -1))
			break ;
		else if (launchcommands(g_buff, child) == 0)
			return (0);
	}
	if (isatty(0))
		ft_goodbye();
	ft_deinit(child, history);
	return (1);
}

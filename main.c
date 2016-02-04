/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 17:00:39 by flagoutt          #+#    #+#             */
/*   Updated: 2016/02/04 09:29:16 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"
#include <stdio.h>

void		set_righthome(t_execdata *data)
{
	char *home;
	char *tmp;

	home = ft_getenv(data->env, "HOME");
	if (!ft_strncmp(home, "/nfs", 4))
	{
		tmp = ft_strjoin("/Volumes/Data", home);
		ft_setenv(data, "HOME", tmp, 1);
		free(tmp);
	}
	free(home);
}

int			pipedcommands(char *buff, t_execdata *child)
{
	char		**commands;
	int			pipedfd[2];
	int			i;

	commands = ft_strsplit(buff, '|');
	i = -1;
	pipe(pipedfd);
	while (commands[++i])
	{
		child->av = ft_spacestrsplit(commands[i]);
		child->fd[0] = 0;
		child->fd[1] = 1;
		if (i)
			child->fd[0] = pipedfd[0];
		if (commands[i + 1])
			child->fd[1] = pipedfd[1];
		printf("fd[0] = %i\nfd[1] = %i\n", child->fd[0], child->fd[1]);
		if (launchprogram(child, NULL) == 0)
			return (0);
		ft_freetab(&(child->av));
	}
	close(pipedfd[0]);
	close(pipedfd[1]);
	ft_freetab(&commands);
	return (1);
}

int			launchcommands(char *buff, t_execdata *child)
{
	char		**commands;
	int			i;

	commands = ft_strsplit(buff, ';');
	i = -1;
	while (commands[++i])
	{
		if (pipedcommands(commands[i], child) == 0)
			return (0);
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
	char		*buff;
	t_execdata	*child;

	if (init(&buff, &child, env) == -1)
		return (-1);
	(void)argc;
	(void)argv;
	ft_welcome();
	while (1)
	{
		checkcanonmode();
		getcwd(buff, BUFF_SIZE);
		showprompt(buff);
		ft_bzero(buff, BUFF_SIZE);
		if ((getinputs(buff) == -1))
			break ;
		else if (launchcommands(buff, child) == 0)
			return (0);
	}
	free(buff);
	ft_deinit(child);
	ft_goodbye();
	return (1);
}

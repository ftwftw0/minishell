/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipedcommands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 16:42:30 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/03 16:44:26 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		 pipedcommands(char *buff, t_execdata *child)
{
	char		**commands;
	int			pipedfd[2];
	int			fdin;
	int			i;

	commands = ft_strsplit(buff, '|');
	i = -1;
	fdin = 0;
	while (commands[++i])
	{
		pipe(pipedfd);
		child->av = ft_spacestrsplit(commands[i]);
		ft_memset((void *)(child->fd), 0, sizeof(int) * MAX_FD);
		child->fd[0] = 0;
		child->fd[1] = 1;
		child->fd[2] = 2;
		if (i)
			child->fd[0] = fdin;
		if (commands[i + 1])
		{
			printf("Not last pipe\n");
			child->fd[1] = pipedfd[1];
		}
		printf("fd[0] = %i\nfd[1] = %i\nfd[2] = %i\n", child->fd[0], \
			   child->fd[1], child->fd[2]);
		if (launchprogram(child, NULL) == 0)
			return (0);
		ft_freetab(&(child->av));
		close(pipedfd[1]);
		fdin = pipedfd[0];
	}
	ft_freetab(&commands);
	return (1);
}

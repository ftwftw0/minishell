/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 16:38:42 by flagoutt          #+#    #+#             */
/*   Updated: 2017/02/02 22:42:26 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		showprompt(char *currentdir)
{
	ft_putstr("\033[33m[");
	ft_putstr(currentdir);
	ft_putstr("]\033[35m$\033[0m ");
	return (1);
}

int		showstringtab(t_execdata *data)
{
	int i;

	i = 0;
	if (!(data->env) || !(data->env[0]))
		return (0);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], data->fd[1]);
	return (1);
}

void	ft_welcome(void)
{
	ft_putstr_fd("\033[43m\033[30m", g_ttyfd);
	ft_putendl_fd("                                                ", g_ttyfd);
	ft_putendl_fd("       __             ____             __       ", g_ttyfd);
	ft_putendl_fd("  ____(  \\         .-'    `-.         /  )____  ", g_ttyfd);
	ft_putendl_fd(" (____    \\___    /  (O  O)  \\    ___/    ____)", g_ttyfd);
	ft_putendl_fd("(____         `--(      )     )---'        ____)", g_ttyfd);
	ft_putendl_fd(" (____    ________\\  \\____/  /________    ____)", g_ttyfd);
	ft_putendl_fd("   (_____/         `-.____.-'         \\_____)   ", g_ttyfd);
	ft_putendl_fd("                                                ", g_ttyfd);
	ft_putstr_fd("\033[37m\033[40m", g_ttyfd);
	ft_putstr_fd("\033[0m\n", g_ttyfd);
}

void	ft_goodbye(void)
{
	ft_putchar_fd('\n', g_ttyfd);
	ft_putstr_fd("\033[43m\033[30m      CHECK ME OUT I CAN BEAT OFF", g_ttyfd);
	ft_putendl_fd("AND PLAY GRAND THEFT                     ", g_ttyfd);
	ft_putendl_fd("      AUTO AT ONCE (BUT NOT MUCH ELSE REALLY)   ", g_ttyfd);
	ft_putendl_fd("                     _                           ", g_ttyfd);
	ft_putendl_fd("                   .(_)_                         ", g_ttyfd);
	ft_putendl_fd("                  /,    \\              .        ", g_ttyfd);
	ft_putendl_fd("                 <_)   (\\                       ", g_ttyfd);
	ft_putendl_fd("                __/._ .-|/_       `    .     '   ", g_ttyfd);
	ft_putendl_fd("                 (   .   )          .  |  .      ", g_ttyfd);
	ft_putendl_fd("                 : .d8b-'/     _     \\.-./    _ ", g_ttyfd);
	ft_putendl_fd(":.-.-..-.-.--._  ( ( Y `n   _________'...`_______", g_ttyfd);
	ft_putendl_fd("/  '-.  . -      : : # .v     .    ---==-----  . ", g_ttyfd);
	ft_putendl_fd(" '-.   ' .-,_.-' ( )_#_/  `-..  -     --     --  ", g_ttyfd);
	ft_putendl_fd("       ._.-'      O/ #      `/:_      --  -      ", g_ttyfd);
	ft_putendl_fd("',   .-'          \"' #        ` `=. . -         ", g_ttyfd);
	ft_putendl_fd(" _.-'                #             `-:           ", g_ttyfd);
	ft_putendl_fd("                     .                           ", g_ttyfd);
	ft_putendl_fd("                     `:                          ", g_ttyfd);
	ft_putendl_fd("                      '                          ", g_ttyfd);
	ft_putstr_fd("\033[37m\033[40m", g_ttyfd);
	ft_putstr_fd("\033[0m\n", g_ttyfd);
}

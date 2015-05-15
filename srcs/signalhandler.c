/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalhandler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/30 15:29:48 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/15 14:04:55 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void		unsetallsignal(void)
{
	if (signal(SIGINT, unhandler) == SIG_ERR)
		exit(1);
	if (signal(SIGTSTP, unhandler) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, unhandler) == SIG_ERR)
		exit(1);
	if (signal(SIGTERM, unhandler) == SIG_ERR)
		exit(1);
	if (signal(SIGSEGV, unhandler) == SIG_ERR)
		exit(1);
}

void		setselectsignal(void)
{
	int i;

	i = 0;
	while (++i < SIGSTOP)
		if (i != SIGKILL && signal(i, selecthandler) == SIG_ERR)
			exit(1);
	if (signal(SIGWINCH, selecthandler) == SIG_ERR)
		exit(1);
	i = 19;
	while (++i < SIGUSR2)
		if (signal(i, selecthandler) == SIG_ERR)
			exit(1);
}

void		setallsignal(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
		exit(1);
	if (signal(SIGTSTP, handler) == SIG_ERR)
		exit(1);
	if (signal(SIGQUIT, handler) == SIG_ERR)
		exit(1);
	if (signal(SIGTERM, handler) == SIG_ERR)
		exit(1);
	if (signal(SIGSEGV, handler) == SIG_ERR)
		exit(1);
}

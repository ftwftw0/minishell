/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 14:04:16 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/15 14:05:12 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void		handler(int signal)
{
	char buff[BUFF_SIZE];

	ft_putchar('\n');
	if (signal == SIGINT)
	{
		getcwd(buff, BUFF_SIZE);
		showprompt(buff);
	}
	else if (signal == SIGSEGV)
	{
		printf("SEGFAUAAAAAULT AAAAAAAAAAAAAHH!!\n");
		ft_deinit(NULL);
		exit(1);
	}
	else if (signal == SIGQUIT)
	{
		ft_deinit(NULL);
		ft_putstr("Trying to quit process ");
		ft_putnbr(getpid());
		ft_putstr(".\n");
		ft_goodbye();
		exit(0);
	}
	else
		printf("Caught signal %d\n", signal);
}

void		unhandler(int signal)
{
	(void)signal;
}

void		selecthandler(int signal)
{
	if (signal == SIGWINCH)
		showlist(g_ftselect->list);
	else
	{
		ft_putstr("Interrupting program because of signal .");
		ft_putnbr(signal);
		ft_putstr(" ...\n");
		deinit();
		exit(1);
	}
}

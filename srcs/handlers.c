/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 14:04:16 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/04 17:19:45 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void		handler(int signal)
{
	char buff[BUFF_SIZE];

	ft_putchar_fd('\n', 2);
	if (signal == SIGINT)
	{
		getcwd(buff, BUFF_SIZE);
		if (isatty(0))
			showprompt(buff);
	}
	else if (signal == SIGSEGV)
	{
		ft_putstr_fd("This is what i call a gay segfault. Yes sir.\n", 2);
		ft_deinit(NULL);
		exit(1);
	}
	else if (signal == SIGQUIT)
	{
		ft_deinit(NULL);
		ft_putstr_fd("Trying to quit process ", 2);
		ft_putnbr_fd(getpid(), 2);
		ft_putstr_fd(".\n", 2);
		if (isatty(0))
			ft_goodbye();
		exit(0);
	}
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
		ft_putstr_fd("Interrupting program because of signal .", 2);
		ft_putnbr_fd(signal, 2);
		ft_putstr_fd(" ...\n", 2);
		deinit();
		exit(1);
	}
}

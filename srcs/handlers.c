/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/15 14:04:16 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/23 07:47:44 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void		handler(int signal)
{
	ft_putchar_fd('\n', 2);
	if (signal == SIGINT)
	{
		ft_bzero(g_buff, BUFF_SIZE);
		getcwd(g_buff, BUFF_SIZE);
		showprompt(g_buff);
		ft_bzero(g_buff, BUFF_SIZE);
		g_cursor = g_buff;
	}
	else if (signal == SIGSEGV)
	{
		ft_putstr_fd("This is what i call a gay segfault. Yes sir.\n", 2);
		ft_deinit(NULL, NULL);
		exit(1);
	}
	else if (signal == SIGQUIT)
	{
		ft_deinit(NULL, NULL);
		ft_putstr_fd("Trying to quit process ", 2);
		ft_putnbr_fd(getpid(), 2);
		ft_putstr_fd(".\n", 2);
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

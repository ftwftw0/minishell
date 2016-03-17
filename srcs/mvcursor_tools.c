/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:40:40 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/17 17:09:34 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	mvctop(void)
{
	char *tmp;

	tmp = tgetstr("up", NULL);
	tputs(tmp, 1, custom_putchar);
}

void	mvcbot(void)
{
	char *tmp;

	tmp = tgetstr("do", NULL);
	tputs(tmp, 1, custom_putchar);
}

void	mvcleft(int size)
{
	struct winsize w;
	char *tmp;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	tmp = tgetstr("le", NULL);
	while (size--)
	{
		if (get_cursor_x() == 1)
		{
			mvctop();
			mvcright(w.ws_col - 1);
		}
		else
			tputs(tmp, 1, custom_putchar);
	}
}

void	mvcright(int size)
{
	struct winsize w;
	char *tmp;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	tmp = tgetstr("nd", NULL);
	while (size--)
	{
		if (get_cursor_x() == w.ws_col)
			tputs(tgetstr("do", NULL), 1, custom_putchar);
		else
			tputs(tmp, 1, custom_putchar);
	}
}

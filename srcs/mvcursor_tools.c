/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:40:40 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/15 18:42:01 by flagoutt         ###   ########.fr       */
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
	char *tmp;

	tmp = tgetstr("le", NULL);
	while (size--)
		tputs(tmp, 1, custom_putchar);
}

void	mvcright(int size)
{
	struct winsize w;
	char *tmp;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	ft_putstr("\033[6n");

	char i = 0;
	read(0, &i, 4);
	printf("i = %i     winsize.x = %i\n", i, w.ws_col);


	tmp = tgetstr("nd", NULL);
	while (size--)
		tputs(tmp, 1, custom_putchar);
}

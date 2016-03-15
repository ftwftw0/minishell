/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:19:47 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/15 16:52:15 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void    mvcstart(char *buff, char **ptr)
{
    mvcleft(*ptr - buff);
    *ptr = buff;
}

void    mvcend(char **ptr)
{
    mvcright(ft_strlen(*ptr));
    *ptr = &(*ptr)[ft_strlen(*ptr)];
}

void    mvclineup(char *buff, char **ptr)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	if (*ptr - buff > w.ws_col)
	{
		mvctop();
		*ptr -= w.ws_col;
	}
}

void    mvclinedown(char *buff, char **ptr)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	(void)buff;
	if (ft_strlen(*ptr) > w.ws_col)
	{
		mvcbot();
		*ptr += w.ws_col;
	}
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:19:47 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/24 07:58:46 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	mvcstart(char *buff, char **ptr)
{
	mvcleft(*ptr - buff);
	*ptr = buff;
}

void	mvcend(char **ptr)
{
	mvcright(ft_strlen(*ptr));
	*ptr = &(*ptr)[ft_strlen(*ptr)];
}

void	mvclineup(char *buff, char **ptr)
{
	struct winsize w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (*ptr - buff >= w.ws_col)
	{
		mvctop();
		*ptr -= w.ws_col;
	}
}

void	mvclinedown(char *buff, char **ptr)
{
	struct winsize	w;
	int				xpos;

	(void)buff;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (ft_strlen(*ptr) > w.ws_col)
	{
		xpos = get_cursor_x();
		mvcbot();
		mvcright(xpos - 1);
		*ptr += w.ws_col;
	}
}

void	mvcnextword(char *buff, char **ptr)
{
	(void)buff;
	while (**ptr && ft_isspace(**ptr))
	{
		(*ptr)++;
		mvcright(1);
	}
	while (**ptr && !ft_isspace(**ptr))
	{
		(*ptr)++;
		mvcright(1);
	}
}

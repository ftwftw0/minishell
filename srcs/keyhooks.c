/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/02 18:26:37 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/15 09:50:18 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	mvcursor(void)
{
	if (g_ftselect->buff[2] == 'A')
		mvtop();
	else if (g_ftselect->buff[2] == 'D')
		mvleft();
	else if (g_ftselect->buff[2] == 'B')
		mvbot();
	else if (g_ftselect->buff[2] == 'C')
		mvright();
}

int			keyhooks(void)
{
	if (g_ftselect->buff[0] == 27)
	{
		if (g_ftselect->buff[2])
			mvcursor();
		else
			return (-1);
	}
	else if (g_ftselect->buff[0] == 4 || g_ftselect->buff[0] == 10)
		return (0);
	else if (g_ftselect->buff[0] == ' ')
	{
		g_ftselect->cursor->selected = (g_ftselect->cursor->selected) ? 0 : 1;
		mvbot();
	}
	else if (g_ftselect->buff[0] == '\\')
		ft_putchar_fd(g_ftselect->buff[1], 2);
	return (1);
}

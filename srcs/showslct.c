/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 15:26:06 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/09 14:39:42 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static void	startreversemode(void)
{
	char *mov;

	mov = tgetstr("mr", NULL);
	tputs(mov, g_ftselect->fd, custom_putchar);
}

static void	putstrpos(int x, int y, const char *str, int size)
{
	int		i;
	char	*mov;

	i = 0;
	mov = tgetstr("cm", NULL);
	tputs(tgoto(mov, x, y), g_ftselect->fd, custom_putchar);
	size = g_ftselect->colsize - size;
	while (++i < size / 2)
		ft_putchar_fd(' ', g_ftselect->fd);
	ft_putstr_fd(str, g_ftselect->fd);
	i = 0;
	size = size - size / 2;
	while (++i < size)
		ft_putchar_fd(' ', g_ftselect->fd);
	mov = tgetstr("me", NULL);
	tputs(mov, g_ftselect->fd, custom_putchar);
}

static void	printlist(t_elem *list, int nbcols)
{
	int x;
	int y;

	x = 1;
	y = 1;
	while (list)
	{
		if (g_ftselect->cursor == list)
			startreversemode();
		putstrpos(x, y, list->name, list->size);
		y++;
		if (y > (g_ftselect->nbelems / nbcols + 1))
		{
			y = 1;
			x += g_ftselect->colsize;
		}
		list = list->next;
	}
}

int			showlist(t_elem *list)
{
	struct winsize	ws;

	if (ioctl(0, TIOCGWINSZ, &ws))
		ft_putstr("Error getting term sizes.");
	g_ftselect->nbcols = ws.ws_col / g_ftselect->colsize;
	cleanterm();
	if (g_ftselect->nbcols * (ws.ws_row - 2) > (g_ftselect->nbelems))
		printlist(list, g_ftselect->nbcols);
	else
		ft_putstr_fd("SMALL", g_ftselect->fd);
	return (1);
}

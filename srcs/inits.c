/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 20:26:14 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/14 17:48:02 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static int		initmaxsize(t_elem *list)
{
	int max;

	max = 0;
	g_ftselect->nbelems = 0;
	while (list)
	{
		if (list->size > max)
			max = list->size;
		g_ftselect->nbelems++;
		list = list->next;
	}
	return (++max);
}

static int		terminit(void)
{
	char			*tmp;

	tmp = tgetstr("cb", NULL);
	tputs(tmp, 1, custom_putchar);
	tmp = tgetstr("cl", NULL);
	tputs(tmp, 1, custom_putchar);
	tmp = tgetstr("vi", NULL);
	tputs(tmp, 1, custom_putchar);
	cleanterm();
	return (1);
}

int				inits(t_elem *list)
{
	if (!(g_ftselect->fd = open("/dev/tty", O_RDWR)))
		g_ftselect->fd = 1;
	g_ftselect->list = list;
	g_ftselect->cursor = list;
	if (terminit() < 0)
		return (-1);
	g_ftselect->colsize = initmaxsize(list) + 1;
	g_ftselect->buff = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 17:08:48 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/14 18:10:35 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	mvright(void)
{
	int i;

	i = g_ftselect->nbelems / g_ftselect->nbcols + 2;
	while (g_ftselect->cursor && --i)
		g_ftselect->cursor = g_ftselect->cursor->next;
	if (i--)
	{
		g_ftselect->cursor = g_ftselect->list;
		while (g_ftselect->cursor->next && --i > 0)
			g_ftselect->cursor = g_ftselect->cursor->next;
	}
}

void	mvbot(void)
{
	if (g_ftselect->cursor->next)
		g_ftselect->cursor = g_ftselect->cursor->next;
	else
		g_ftselect->cursor = g_ftselect->list;
}

void	mvleft(void)
{
	int i;

	i = g_ftselect->nbelems / g_ftselect->nbcols + 2;
	while (g_ftselect->cursor && --i)
		g_ftselect->cursor = g_ftselect->cursor->prev;
	if (i--)
	{
		g_ftselect->cursor = g_ftselect->list;
		while (g_ftselect->cursor->next)
			g_ftselect->cursor = g_ftselect->cursor->next;
		while (g_ftselect->cursor->prev && i-- > 0)
			g_ftselect->cursor = g_ftselect->cursor->prev;
	}
}

void	mvtop(void)
{
	t_elem *list;

	if (g_ftselect->cursor->prev)
		g_ftselect->cursor = g_ftselect->cursor->prev;
	else
	{
		list = g_ftselect->list;
		while (list->next)
			list = list->next;
		g_ftselect->cursor = list;
	}
}

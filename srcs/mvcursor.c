/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 21:49:56 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/11 17:47:32 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	history_up(char *buff, char **ptr, t_history *history)
{
	if (buff && history->current > 0 && history->size > 0)
	{
		if (history->current == history->size)
		{
			if (history->history[history->size])
				free(history->history[history->size]);
			history->history[history->size] = ft_strdup(buff);
			}
		history->current--;
		mvcleft(*ptr - buff);
		ft_memset(buff, ' ', ft_strlen(buff));
		ft_putstr(buff);
		mvcleft(ft_strlen(buff));
		ft_bzero(buff, BUFF_SIZE);
		ft_strcpy(buff, history->history[history->current]);
		ft_putstr(buff);
		*ptr = buff + ft_strlen(buff);
		**ptr = '\0';
	}
}

static void	history_down(char *buff, char **ptr, t_history *history)
{
	if (buff && (history->current < history->size))
	{
		history->current++;
		ft_memset(buff, ' ', ft_strlen(buff));
		mvcleft(*ptr - buff);
		ft_putstr(buff);
		mvcleft(ft_strlen(buff));
		ft_bzero(buff, BUFF_SIZE);
		if (history->history[history->current] != NULL)
			ft_strcpy(buff, history->history[history->current]);
		ft_putstr(buff);
		*ptr = buff + ft_strlen(buff);
		**ptr = '\0';
	}
}

void		mvcursor(char *buff, char **ptr, t_history *history)
{
	char inputs[4];

	read(0, inputs, 2);
	if (inputs[1] == 'A' && history)
		history_up(buff, ptr, history);
	else if (inputs[1] == 'D' && buff < (*ptr))
	{
		mvcleft(1);
		(*ptr)--;
	}
	else if (inputs[1] == 'B' && history)
		history_down(buff, ptr, history);
	else if (inputs[1] == 'C' && *(*ptr))
	{
		mvcright(1);
		(*ptr)++;
	}
	else if (inputs[1] == 72)
		mvcstart(buff, ptr);
	else if (inputs[1] == 70)
		mvcend(ptr);
}

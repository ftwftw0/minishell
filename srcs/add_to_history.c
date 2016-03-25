/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 14:16:04 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/25 14:36:25 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int	add_to_history(char *buff, t_history *history)
{
	if (!history || !buff)
		return (-1);
	if (history->history[history->size] != NULL)
	{
		free(history->history[history->size]);
		history->history[history->size] = NULL;
	}
	if (buff[0] && ft_strlen(buff) > 0 &&
		(history->size == 0 ||
		ft_strcmp(buff, history->history[history->size - 1])))
	{
		history->history[history->size] = NULL;
		add_str_to_tab(&(history->history), buff);
		history->current = history->size++;
		ft_putendl_fd(buff, history->fd);
	}
	history->current = history->size;
	return (0);
}

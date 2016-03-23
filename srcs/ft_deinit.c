/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_deinit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 18:36:00 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/23 07:11:16 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	deinit_norm(t_history *history)
{
	if (history)
	{
		ft_freetab(&(history->history));
		close(history->fd);
	}
	close(g_ttyfd);
	free(g_buff);
}

int			ft_deinit(t_execdata *data, t_history *history)
{
	if (data != NULL)
	{
		ft_freetab(&(data->av));
		ft_freetab(&(data->env));
		free(data);
	}
	termdeinit();
	deinit_norm(history);
	return (1);
}

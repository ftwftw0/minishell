/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 19:59:44 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/15 13:23:49 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static char	*loopselect(t_elem *list)
{
	char	*chosen;
	int		ret;

	chosen = NULL;
	ret = 0;
	while (g_ftselect->list)
	{
		ft_bzero(g_ftselect->buff, BUFF_SIZE);
		showlist(g_ftselect->list);
		if (read(0, g_ftselect->buff, 3) == -1)
			return (chosen);
		if ((ret = keyhooks()) <= 0)
		{
			if (ret == 0)
			{
				while (list != g_ftselect->cursor)
					list = list->next;
				chosen = ft_strdup(list->name);
			}
			return (chosen);
		}
	}
	return (chosen);
}

char		*ft_select(t_elem *list)
{
	char	*chosen;

	chosen = NULL;
	g_ftselect = (t_selectdata *)malloc(sizeof(t_selectdata));
	if (inits(list) == -1)
	{
		free(g_ftselect);
		return (NULL);
	}
	chosen = loopselect(list);
	deinit();
	free(g_ftselect);
	return (chosen);
}

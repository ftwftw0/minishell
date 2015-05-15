/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getindex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/05 16:07:40 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/09 19:20:16 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_elem	*getadress(t_elem *list, int index)
{
	int i;

	i = 1;
	while (list)
	{
		if (i == index)
			return (list);
		i++;
		list = list->next;
	}
	return (NULL);
}

int		getindex(t_elem *list, t_elem *theone)
{
	int i;

	i = 1;
	while (list)
	{
		if (list == theone)
			return (i);
		i++;
		list = list->next;
	}
	return (0);
}

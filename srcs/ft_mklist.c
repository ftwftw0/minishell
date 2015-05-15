/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mklist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 20:12:59 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/11 20:52:44 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

static t_elem	*newelem(char *name)
{
	t_elem	*elem;

	if ((elem = (t_elem *)malloc(sizeof(t_elem))))
	{
		elem->name = ft_strdup(name);
		elem->size = ft_strlen(name);
		elem->selected = 0;
		elem->prev = NULL;
		elem->next = NULL;
		return (elem);
	}
	return (NULL);
}

t_elem			*ft_mkselecteds(t_elem *list)
{
	t_elem	*selecteds;
	t_elem	*tmp;

	while (list && !(list->selected))
		list = list->next;
	if (!list)
		return (NULL);
	selecteds = newelem(list->name);
	selecteds->selected = 1;
	tmp = selecteds;
	list = list->next;
	while (list)
	{
		if (list->selected && (tmp->next = newelem(list->name)))
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		list = list->next;
	}
	return (selecteds);
}

t_elem			*ft_mklist(int argc, char **argv)
{
	t_elem	*list;
	t_elem	*tmp;
	int		i;

	i = 1;
	list = newelem(argv[1]);
	tmp = list;
	while (++i < argc)
	{
		if ((tmp->next = newelem(argv[i])))
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
	}
	return (list);
}

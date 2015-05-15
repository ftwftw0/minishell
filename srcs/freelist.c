/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freelist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/06 19:58:03 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/09 18:58:27 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	freelist(t_elem *list)
{
	t_elem *tmp;

	while ((tmp = list))
	{
		list = list->next;
		free(tmp->name);
		free(tmp);
	}
}

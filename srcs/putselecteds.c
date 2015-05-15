/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putselecteds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/07 15:10:56 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/09 18:37:11 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	putselecteds(t_elem *list)
{
	while (list)
	{
		ft_putstr(list->name);
		ft_putchar(' ');
		list = list->next;
	}
}

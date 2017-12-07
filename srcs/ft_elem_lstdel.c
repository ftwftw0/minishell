/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_lstdel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 19:53:47 by flagoutt          #+#    #+#             */
/*   Updated: 2017/11/11 20:42:53 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	ft_elem_lstdel(t_elem **alst)
{
	t_elem		*tmp;

	if (!alst || !*alst)
		return ;
	tmp = *alst;
	while (tmp)
	{
		tmp = (*alst)->next;
		if (!alst || !(*alst))
			return ;
		free((*alst)->name);
		(*alst)->name = NULL;
		(*alst)->size = 0;
		(*alst)->prev = NULL;
		(*alst)->next = NULL;
		free(*alst);
		*alst = tmp;
	}
	*alst = NULL;
}

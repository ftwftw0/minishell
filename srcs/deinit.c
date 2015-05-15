/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 16:51:52 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/13 16:27:43 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	deinit(void)
{
	char *tmp;

	cleanterm();
	tmp = tgetstr("ve", NULL);
	tputs(tmp, 1, custom_putchar);
	setallsignal();
}

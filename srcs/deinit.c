/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deinit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 16:51:52 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/10 13:24:15 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	deinit(void)
{
	char	*tmp;
	int		i;

	i = 100;
	cleanterm();
	tmp = tgetstr("ve", NULL);
	tputs(tmp, 1, custom_putchar);
	tmp = tgetstr("te", NULL);
	tputs(tmp, 1, custom_putchar);
	setallsignal();
	while (i--)
		tputs(tgetstr("le", NULL), 1, custom_putchar);
}

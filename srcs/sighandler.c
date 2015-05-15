/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 19:34:06 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/09 19:34:28 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		handler(int signal)
{
	if (signal == SIGWINCH)
		showlist(g_ftselect->list);
	else
	{
		ft_putstr("Interrupting program because of signal .");
		ft_putnbr(signal);
		ft_putstr(" ...\n");
		deinit();
		exit(1);
	}
}

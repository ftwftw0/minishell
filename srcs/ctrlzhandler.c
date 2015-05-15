/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrlzhandler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 19:32:58 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/10 17:37:01 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void		pausectrlz(int signb)
{
	char	cp[2];
	char	*tmp;

	cp[0] = g_ftselect->term.c_cc[VSUSP];
	cp[1] = 0;
	if (signb == SIGTSTP)
	{
		if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
			exit(0);
		ft_putstr("Pausing ... Type fg to continue.");
		tmp = tgetstr("ve", NULL);
		tputs(tmp, 1, custom_putchar);
		ioctl(0, TIOCSTI, cp);
	}
	else if (signb == SIGCONT)
	{
		inits(g_ftselect->list);
		showlist(g_ftselect->list);
		if (signal(SIGTSTP, pausectrlz) == SIG_ERR)
			exit(1);
	}
}

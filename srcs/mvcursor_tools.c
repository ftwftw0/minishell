/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:40:40 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/10 14:56:39 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	mvctop(void)
{
	char *tmp;

	tmp = tgetstr("up", NULL);
	tputs(tmp, 1, custom_putchar);
}

void	mvcbot(void)
{
	char *tmp;

	tmp = tgetstr("do", NULL);
	tputs(tmp, 1, custom_putchar);
}

void	mvcleft(int size)
{
	char *tmp;

	tmp = tgetstr("le", NULL);
	while (size--)
		tputs(tmp, 1, custom_putchar);
}

void	mvcright(int size)
{
	char *tmp;

	tmp = tgetstr("nd", NULL);
	while (size--)
		tputs(tmp, 1, custom_putchar);
}

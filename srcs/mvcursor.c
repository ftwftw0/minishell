/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 21:49:56 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/15 14:00:13 by flagoutt         ###   ########.fr       */
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

void	mvcleft(void)
{
	char *tmp;

	tmp = tgetstr("le", NULL);
	tputs(tmp, 1, custom_putchar);
}

void	mvcright(void)
{
	char *tmp;

	tmp = tgetstr("nd", NULL);
	tputs(tmp, 1, custom_putchar);
}

void	mvcursor(char inputs[10], char *buff, char **ptr)
{
	if (inputs[2] == 'A')
		(0) ? mvctop() : (void)inputs;
	else if (inputs[2] == 'D' && buff < (*ptr))
	{
		mvcleft();
		(*ptr)--;
	}
	else if (inputs[2] == 'B')
		(0) ? mvcbot() : (void)inputs;
	else if (inputs[2] == 'C' && *(*ptr))
	{
		mvcright();
		(*ptr)++;
	}
}

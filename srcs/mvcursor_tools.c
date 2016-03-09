/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:40:40 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/09 14:41:46 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"


void    mvctop(void)
{
    char *tmp;

    tmp = tgetstr("up", NULL);
    tputs(tmp, 1, custom_putchar);
}

void    mvcbot(void)
{
    char *tmp;

    tmp = tgetstr("do", NULL);
    tputs(tmp, 1, custom_putchar);
}

void    mvcleft(int size)
{
    char *tmp;

    tmp = tgetstr("le", NULL);
    while (size--)
        tputs(tmp, 1, custom_putchar);
}

void    mvcright(int size)
{
    char *tmp;

    tmp = tgetstr("nd", NULL);
    while (size--)
        tputs(tmp, 1, custom_putchar);
}

void    mvcstart(char *buff, char **ptr)
{
    mvcleft(*ptr - buff);
    *ptr = buff;
}

void    mvcend(char **ptr)
{
    mvcright(ft_strlen(*ptr));
    *ptr = &(*ptr)[ft_strlen(*ptr)];
}

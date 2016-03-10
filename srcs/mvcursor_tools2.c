/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor_tools2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:19:47 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/10 16:20:08 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

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

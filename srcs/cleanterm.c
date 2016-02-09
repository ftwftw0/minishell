/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanterm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/09 19:35:20 by flagoutt          #+#    #+#             */
/*   Updated: 2016/02/09 11:11:04 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void			cleanterm(void)
{
	char *tmp;

	tmp = tgetstr("ho", NULL);
	tputs(tmp, 1, custom_putchar);
	tmp = tgetstr("cd", NULL);
	tputs(tmp, 1, custom_putchar);
}

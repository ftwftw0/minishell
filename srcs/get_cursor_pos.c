/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:30:22 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/17 16:38:34 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int	get_cursor_y(void)
{
    char bff[20];
    int ret;

	ft_putstr("\033[6n");
	ret = read(0, bff, 20);
    bff[ret] = '\0';
	ret = ft_atoi(&bff[2]);
	return (ret);
}

int	get_cursor_x(void)
{
    char bff[20];
    int ret;

	ft_putstr("\033[6n");
	ret = read(0, bff, 20);
    bff[ret] = '\0';
	ret = ft_atoi(&bff[2 + ft_intlen(ft_atoi(&bff[2])) + 1]);
	return (ret);
}



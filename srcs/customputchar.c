/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   customputchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/05 18:59:41 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/14 16:44:55 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			custom_putchar(int c)
{
	write(1, &c, 1);
	return (c);
}

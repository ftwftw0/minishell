/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 08:59:27 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/24 09:00:13 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static int  check_parity(char *buff, char c, char d)
{
	char *ptr;

	ptr = buff - 1;
	while ((ptr = ft_strchr(ptr + 1, c)))
		if (!(ptr = ft_strchr(ptr + 1, d)))
			return (0);
	return (1);
}

int  command_well_formated(char *buff)
{
	if (!check_parity(buff, '\'', '\'') ||
		!check_parity(buff, '"', '"') ||
		!check_parity(buff, '`', '`') ||
		!check_parity(buff, '(', ')') ||
		!check_parity(buff, '[', ']') ||
		!check_parity(buff, '{', '}'))
		return (0);
	return (1);
}

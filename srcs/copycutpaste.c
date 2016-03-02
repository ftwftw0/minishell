/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copycutpaste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:42:46 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/02 20:45:13 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void copycutpaste(char input, char *buff, char **ptr)
{
	static int	startpos = -1;
	static char	copy[BUFF_SIZE];
	char		inputs[3];

	read(0, inputs, 2);
	if (input == -61 && inputs[0] == -89)
// Copy - Alt^C
	  {
		if (startpos == -1) // Start copy
		{
			startpos = *ptr - buff;
			ft_putstr("\033[7m");
			ft_putchar(**ptr);
			ft_putstr("\033[00m");
			mvcleft(1);
		}
		else
		{
			ft_strncpy(copy, &buff[startpos], *ptr - buff - startpos);
			mvcleft(*ptr - buff - startpos);
			*ptr = &buff[startpos];
			ft_putstr(*ptr);
			mvcleft(ft_strlen(*ptr));
			startpos = -1;
		}
    }
       	else if (input == -30 && inputs[0] == -119 && startpos != -1)
// Cut - Alt^X
    {
		ft_strncpy(copy, &buff[startpos], *ptr - buff - startpos);
		mvcleft(*ptr - buff - startpos);

		ft_memmove(&buff[startpos], *ptr, ft_strlen(*ptr) + 1);
		
		ft_memset(&buff[ft_strlen(buff)], ' ', ft_strlen(copy));
		
		*ptr = &buff[startpos];
		ft_putstr(*ptr);
		mvcleft(ft_strlen(*ptr));

		buff[ft_strlen(buff) - ft_strlen(copy)] = 0; // Sets the \0

		startpos = -1;
    }
	else if (input == -30 && inputs[0] == -120)
// Paste - Alt^V
    {
		ft_memmove(*ptr, copy, ft_strlen(copy));
		ft_putstr(*ptr);
		mvcleft(ft_strlen(*ptr));
    }

}


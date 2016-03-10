/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copycutpaste.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/02 14:42:46 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/10 14:24:31 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	alt_c_endcopy(char *buff, char **ptr, int *startpos, char *copy)
{
	int tmp;

	tmp = 0;
	if ((int)(*ptr - buff) < *startpos)
	{
		tmp = *startpos;
		*startpos = *ptr - buff;
		*ptr = buff + tmp;
		mvcright(*ptr - buff - *startpos);
	}
	else
			mvcleft(*ptr - buff - *startpos);
	ft_strncpy(copy, &buff[*startpos], *ptr - buff - *startpos);
	*ptr = &buff[*startpos];
	if (tmp)
		*ptr = &buff[tmp];
	ft_putstr(*ptr);
	mvcleft(ft_strlen(*ptr));
	*startpos = -1;
}

static void	alt_c_copy(char *buff, char **ptr, int *startpos, char *copy)
{
	if (*startpos == -1)
	{
		*startpos = *ptr - buff;
		ft_putstr("\033[7m");
		if (*ptr == &buff[ft_strlen(buff)])
			ft_putchar(' ');
		ft_putchar(**ptr);
		ft_putstr("\033[00m");
		mvcleft(1);
	}
	else
		alt_c_endcopy(buff, ptr, startpos, copy);
}

static void	alt_x_cut(char *buff, char **ptr, int *startpos, char *copy)
{
	int tmp;

	tmp = 0;
	if (*ptr - buff < *startpos)
	{
		tmp = *startpos;
		*startpos = *ptr - buff;
		*ptr = buff + tmp;
		mvcright(*ptr - buff - tmp);
	}
	else
		mvcleft(*ptr - buff - *startpos);
	ft_strncpy(copy, &buff[*startpos], *ptr - buff - *startpos);
	ft_memmove(&buff[*startpos], *ptr, ft_strlen(*ptr) + 1);
	ft_memset(&buff[ft_strlen(buff)], ' ', ft_strlen(copy) + 1);
	*ptr = &buff[*startpos];
	ft_putstr(*ptr);
	mvcleft(ft_strlen(*ptr));
	buff[ft_strlen(buff) - 1 - ft_strlen(copy)] = 0;
	ft_bzero(&buff[ft_strlen(buff)], BUFF_SIZE - ft_strlen(buff));
	*startpos = -1;
}

static void	alt_v_paste(char **ptr, char *copy)
{
	ft_memmove(*ptr + ft_strlen(copy), *ptr, ft_strlen(*ptr));
	ft_memmove(*ptr, copy, ft_strlen(copy));
	ft_putstr(*ptr);
	mvcleft(ft_strlen(*ptr));
}

void		copycutpaste(char input, char *buff, char **ptr)
{
	static int	startpos = -1;
	static char	copy[BUFF_SIZE];
	char		inputs[3];

	read(0, inputs, 2);
	if (input == -61 && inputs[0] == -89)
		alt_c_copy(buff, ptr, &startpos, (char *)copy);
	else if (input == -30 && inputs[0] == -119 && startpos != -1)
		alt_x_cut(buff, ptr, &startpos, (char *)copy);
	else if (input == -30 && inputs[0] == -120)
		alt_v_paste(ptr, (char *)copy);
}

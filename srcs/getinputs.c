/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 19:12:05 by flagoutt          #+#    #+#             */
/*   Updated: 2016/02/12 15:00:22 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	mvbackspace(char *buff, char **ptr)
{
	char	*tmp;
	int		i;
	int		j;

	tmp = (*ptr);
	j = 0;
	if ((*ptr) > buff)
	{
		i = ft_strlen(tmp);
		(*ptr)--;
		mvcleft();
		ft_putstr((tmp));
		ft_putchar(' ');
		ft_strcpy((*ptr), tmp);
		j = 0;
		while (j++ <= i)
			mvcleft();
	}
}

static int	checkinputs(char inputs[10], char *buff, char **ptr)
{
	int i;

	if (inputs[0] == 27 && (inputs[2]))
		mvcursor(inputs, buff, ptr);
	else if (inputs[0] == '\n')
		return (1);
	else if (inputs[0] == 4)
	{
		if (buff[0] == '\0')
			return (-1);
		return (0);
	}
	else if (inputs[0] == 127 || inputs[0] == 126)
		mvbackspace(buff, ptr);
	else if (inputs[0] == 9)
		completion(buff, ptr);
	else if (ft_isprint(inputs[0]))
	{
		ft_memmove((*ptr) + 1, (*ptr), ft_strlen((*ptr)));
		(*ptr)[0] = inputs[0];
		ft_putstr(*ptr);

		i = ft_strlen(*ptr);
		while (--i)
			mvcleft();
		(*ptr)++;
	}
	return (2);
}

int			getinputs(char *buff)
{
	char	inputs[10];
	char	*ptr;
	int		ret;

	ptr = buff;
	while ((ret = read(0, inputs, 10)) > 0)
	{
		inputs[ret] = '\0';
		if ((ret = checkinputs(inputs, buff, &ptr)) <= 1)
			break ;
		else if (ret == -1)
			return (-1);
		ft_bzero(inputs, 9);
	}
	ft_putchar('\n');
	return (ret);
}

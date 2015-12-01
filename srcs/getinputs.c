/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 19:12:05 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/15 14:46:49 by flagoutt         ###   ########.fr       */
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
	if (inputs[0] == 27 && (inputs[2]))
		mvcursor(inputs, buff, ptr);
	else if (inputs[0] == '\n')
		return (0);
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
		ft_putchar(inputs[0]);
		(*ptr)[0] = inputs[0];
		(*ptr)++;
	}
	return (1);
}

int			getinputs(char *buff)
{
	char	inputs[10];
	char	*ptr;
	int		ret;

	ptr = buff;
	while ((ret = read(0, inputs, 10)) != EOF)
	{
		inputs[ret] = '\0';
		if ((ret = checkinputs(inputs, buff, &ptr)) == 0)
			break ;
		else if (ret == -1)
			return (-1);
		ft_bzero(inputs, 9);
	}
	ft_putchar('\n');
	return (ret);
}
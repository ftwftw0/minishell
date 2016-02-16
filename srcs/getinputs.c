/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 19:12:05 by flagoutt          #+#    #+#             */
/*   Updated: 2016/02/16 16:43:38 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	mvbackspace(char *buff, char **ptr)
{
	char	*tmp;
	int		i;

	tmp = (*ptr);
	if ((*ptr) > buff)
	{
		i = ft_strlen(tmp);
		(*ptr)--;
		mvcleft(1);
		ft_putstr((tmp));
		ft_putchar(' ');
		ft_strcpy((*ptr), tmp);
		mvcleft(i);
	}
}

static int	checkinputs(char inputs[10], char *buff, char **ptr, t_history *history)
{
	if (inputs[0] == 27 && (inputs[2]))
		mvcursor(inputs, buff, ptr, history);
	else if (inputs[0] == '\n')
	{
		if (buff[0])
		{
			if (history->history[history->size])
			{
				free(history->history[history->size]);
				history->history[history->size] = NULL;
			}
			add_str_to_tab(&(history->history), buff);
			history->current = history->size;
			history->size++;
		}
		history->current = ft_tablen(history->history);
		return (1);
	}
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
		mvcleft(ft_strlen(*ptr) - 1);
		(*ptr)++;
	}
	return (2);
}

int			getinputs(char *buff, t_history *history)
{
	char	inputs[10];
	char	*ptr;
	int		ret;

	ptr = buff;
	while ((ret = read(0, inputs, 10)) > 0)
	{
		inputs[ret] = '\0';
		if ((ret = checkinputs(inputs, buff, &ptr, history)) <= 1)
			break ;
		else if (ret == -1)
			return (-1);
		ft_bzero(inputs, 9);
	}
	ft_putchar('\n');
	return (ret);
}

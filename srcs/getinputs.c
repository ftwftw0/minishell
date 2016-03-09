/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 19:12:05 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/09 14:13:52 by flagoutt         ###   ########.fr       */
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
		mvcleft(i + 1);
	}
}

static void checkinputs_splitted(char input, char *buff, char **ptr, t_history *history)
{
	if (input == 127 || input == 126)
		mvbackspace(buff, ptr);
	else if (input == 9)
		completion(buff, ptr);
	else if (input < 0) // Alt-C pour debuter le copier
		copycutpaste(input, buff, ptr);
	else if (input == 1) // Ctrl-A pour aller en debut de ligne
		mvcstart(buff, ptr);
	else if (input == 5) // Ctrl-E pour aller en fin de ligne
		mvcend(ptr);
	else if (input == 27)
		mvcursor(buff, ptr, history);
	else if (ft_isprint(input))
	{
		ft_memmove((*ptr) + 1, (*ptr), ft_strlen((*ptr)));
		(*ptr)[0] = input;
		if (isatty(0))
			ft_putstr(*ptr);
		mvcleft(ft_strlen(*ptr) - 1);
		(*ptr)++;
	}
}

static int	checkinputs(char input, char *buff, char **ptr, t_history *history)
{
	if (input == '\n')
	{
		if (history->history[history->size] != NULL)
		{
			free(history->history[history->size]);
			history->history[history->size] = NULL;
		}
		if (buff[0] && ft_strlen(buff) > 0 &&
			(history->size == 0 || ft_strcmp(buff, history->history[history->size - 1])))
		{
			history->history[history->size] = NULL;
			add_str_to_tab(&(history->history), buff);
			history->current = history->size;
			history->size++;
		}
		history->current = history->size;
		return (1);
	}
	else if (input == 4)
	{
		if (buff[0] == '\0')
			return (-1);
		return (0);
	}
		checkinputs_splitted(input, buff, ptr, history);
	return (2);
}

int			getinputs(char *buff, t_history *history)
{
	char	input;
	char	*ptr;
	int		ret;

	ptr = buff;
	while ((ret = read(0, &input, 1)) >= 0)
	{
		if (ret == 0 && input == 0)
			return (-1);
		if ((ret = checkinputs(input, buff, &ptr, history)) <= 1)
			break ;
		else if (ret == -1)
			return (-1);
		input = 0;
	}
	ft_putchar('\n');
	return (ret);
}

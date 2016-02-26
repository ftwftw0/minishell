/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mvcursor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 21:49:56 by flagoutt          #+#    #+#             */
/*   Updated: 2016/02/16 17:43:44 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

void	mvctop(void)
{
	char *tmp;

	tmp = tgetstr("up", NULL);
	tputs(tmp, 1, custom_putchar);
}

void	mvcbot(void)
{
	char *tmp;

	tmp = tgetstr("do", NULL);
	tputs(tmp, 1, custom_putchar);
}

void	mvcleft(int size)
{
	char *tmp;

	tmp = tgetstr("le", NULL);
	while (size--)
		tputs(tmp, 1, custom_putchar);
}

void	mvcright(void)
{
	char *tmp;

	tmp = tgetstr("nd", NULL);
	tputs(tmp, 1, custom_putchar);
}

void	mvcursor(char inputs[10], char *buff, char **ptr, t_history *history)
{
	if (inputs[2] == 'A' && history)
	{
		if (buff && history->current > 0 && history->size > 0)
		{
			if (history->current == history->size)
			{
				if (history->history[history->size])
					free(history->history[history->size]);
				history->history[history->size] = ft_strdup(buff);
			}
			history->current--;
			mvcleft(*ptr - buff);
			ft_memset(buff, ' ', ft_strlen(buff));
			ft_putstr(buff);
			mvcleft(ft_strlen(buff));
			ft_bzero(buff, BUFF_SIZE);
			ft_strcpy(buff, history->history[history->current]);
			ft_putstr(buff);
			*ptr = buff + ft_strlen(buff);
			**ptr = '\0';
		}
	}
	else if (inputs[2] == 'D' && buff < (*ptr))
	{
		mvcleft(1);
		(*ptr)--;
	}
	else if (inputs[2] == 'B' && history)
	{
		if (buff && (history->current < history->size))
		{
			history->current++;
			ft_memset(buff, ' ', ft_strlen(buff));
			mvcleft(*ptr - buff);
			ft_putstr(buff);
			mvcleft(ft_strlen(buff));
			ft_bzero(buff, BUFF_SIZE);
			if (history->history[history->current] != NULL)
				ft_strcpy(buff, history->history[history->current]);
			ft_putstr(buff);
			*ptr = buff + ft_strlen(buff);
			**ptr = '\0';
		}
	}
	else if (inputs[2] == 'C' && *(*ptr))
	{
		mvcright();
		(*ptr)++;
	}
}

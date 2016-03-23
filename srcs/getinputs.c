/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getinputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/10 19:12:05 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/23 07:46:46 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	mvbackspace(char *buff, char **ptr)
{
    struct winsize w;
	char	*tmp;
	int		i;

	tmp = (*ptr);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if ((*ptr) > buff)
	{
		i = ft_strlen(tmp);
		(*ptr)--;
		ft_memmove((*ptr), tmp, i + 1);
		mvcleft(1);
		ft_putstr(*ptr);
		if (get_cursor_x() > w.ws_col)
			mvcbot();
		tmp = tgetstr("ce", NULL);
		tputs(tmp, 1, custom_putchar);
		mvcleft(i);
	}
}

static void	checkinputs_splitted(char input, char *buff,
								char **ptr, t_history *history)
{
	if (input == 127)
		mvbackspace(buff, ptr);
	else if (input == 126)
	{
		ft_putchar('~');
		**ptr = '~';
		(*ptr)++;
	}
	else if (input == 9)
		completion(buff, ptr);
	else if (input < 0)
		copycutpaste(input, buff, ptr);
	else if (input == 1)
		mvcstart(buff, ptr);
	else if (input == 5)
		mvcend(ptr);
	else if (input == 27)
		mvcursor(buff, ptr, history);
	else if (ft_isprint(input))
	{
		ft_memmove((*ptr) + 1, (*ptr), ft_strlen((*ptr)));
		(*ptr)[0] = input;
		ft_putstr(*ptr);
		mvcleft(ft_strlen(*ptr) - 1);
		(*ptr)++;
	}
}

static int	add_to_history(char *buff, t_history *history)
{
	if (history->history[history->size] != NULL)
	{
		free(history->history[history->size]);
		history->history[history->size] = NULL;
	}
	if (buff[0] && ft_strlen(buff) > 0 &&
		(history->size == 0 ||
		 ft_strcmp(buff, history->history[history->size - 1])))
	{
		history->history[history->size] = NULL;
		add_str_to_tab(&(history->history), buff);
		history->current = history->size++;
		ft_putendl_fd(buff, history->fd);
	}
	history->current = history->size;
	return (0);
}

static int	checkinputs(char input, char *buff, char **ptr, t_history *history)
{
	if (input == '\n')
	{
		add_to_history(buff, history);
		mvcright(ft_strlen(*ptr));
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

static int	check_parity(char *buff, char c, char d)
{
	char *ptr;

	ptr = buff - 1;
	while ((ptr = ft_strchr(ptr + 1, c)))
		if (!(ptr = ft_strchr(ptr + 1, d)))
			return (0);
	return (1);
}

static int	command_well_formated(char *buff)
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

int			getinputs(char *buff, t_history *history)
{
	char	input;
	int		ret;

	g_cursor = buff;
	input = 0;
	while ((ret = read(0, &input, 1)) >= 0)
	{
		if (ret == 0)
			return (-1);
		ret = checkinputs(input, buff, &g_cursor, history);
		if (ret <= 1)
		{
			while (!command_well_formated(buff))
			{
				ft_putstr("\n > ");
				g_cursor = &buff[ft_strlen(buff)];
				while (read(0, &input, 1) && 
					   (ret = checkinputs(input, &buff[ft_strlen(buff)], &g_cursor, history)) > 1)
					;
			}
			break ;
		}
		else if (ret == -1)
			return (-1);
		input = 0;
	}
	ft_putchar('\n');
	return (ret);
}

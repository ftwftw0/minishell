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
		mvcleft(i + 1);
	}
}

static void	copycutpaste(char inputs[3], char *buff, char **ptr)
{
  static int	startpos = -1;
  static char	copy[BUFF_SIZE];

  if (inputs[0] == -61 && inputs[1] == -89) // Copy - Alt^C
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
	  mvcleft(*ptr - buff - startpos);
	  *ptr = &buff[startpos];
	  ft_putstr(*ptr);
	  mvcleft(ft_strlen(*ptr));
	  ft_strncpy(copy, &buff[startpos], *ptr - buff - startpos);
//	  printf("just copied : %s\n", copy);
	  startpos = -1;
	}
    }
  else if (inputs[0] == -30 && inputs[1] == -119) // Cut - Alt^X
    {
	  startpos = -1;
	  tputs(tgetstr("me", NULL), 1, custom_putchar);
	  ft_strncpy(copy, &buff[startpos], *ptr - buff - startpos);
    }
  else if (inputs[0] == -30 && inputs[1] == -120) // Paste - Alt^X
    {
      ft_strncpy(*ptr, copy, ft_strlen(copy));
    }

}

static int	checkinputs(char inputs[3], char *buff, char **ptr, t_history *history)
{
	if (inputs[0] == 27 && (inputs[2]))
		mvcursor(inputs, buff, ptr, history);
	else if (inputs[0] == '\n')
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
	else if (inputs[0] < 0) // Alt-C pour debuter le copier
	  copycutpaste(inputs, buff, ptr);
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
	char	inputs[4];
	char	*ptr;
	int	ret;

	ptr = buff;
	while ((ret = read(0, inputs, 4)) > 0)
	{
		inputs[ret] = '\0';
		if ((ret = checkinputs(inputs, buff, &ptr, history)) <= 1)
			break ;
		else if (ret == -1)
			return (-1);
//		printf("%i - %i - %i - %i\n", inputs[0], inputs[1], inputs[2], inputs[3]);
		ft_bzero(inputs, 3);
	}
	ft_putchar('\n');
	return (ret);
}

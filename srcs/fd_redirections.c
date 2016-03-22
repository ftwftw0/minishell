/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:45:47 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/22 16:18:04 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	rmv_entries_in_avtable(char ***avptra)
{
	char	**avptrb;
	char	**avptrtmp;

	avptrb = (*avptra) + 2;
	free(*(*avptra));
	*(*avptra) = NULL;
	free(*((*avptra) + 1));
	*((*avptra) + 1) = NULL;
	avptrtmp = *avptra;
	while (*avptrb)
	{
		*avptrtmp = *avptrb;
		*avptrb = NULL;
		avptrtmp++;
		avptrb++;
	}
}

int			out_to_file(t_execdata *data, char ***avptra, int append)
{
	append = (append) ? O_APPEND : 0;
	data->fd[1] = open(*((*avptra) + 1), O_CREAT | O_RDWR | O_TRUNC | append,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	rmv_entries_in_avtable(avptra);
	return (0);
}

int			in_from_file(t_execdata *data, char ***avptra)
{
	int	 fd;

	fd = open(*((*avptra) + 1), O_RDWR);
	if (fd == -1)
	{
		ft_putstr("This file cannot be opened.\n");
		return (-1);
	}
	else
		data->fd[0] = fd;
	rmv_entries_in_avtable(avptra);
	return (0);
}

static void	ctrlhandlstdin(int signal)
{
	(void)signal;
	ft_putstr("\nheredoc > ");
}

int			in_from_stdin(t_execdata *data, char ***avptra)
{
	char	buff[BUFF_SIZE];
	int	 pipedfd[2];
	int	 ret;

	if (!ft_strcmp(*((*avptra) + 1), "EOF"))
	{
		free(*((*avptra) + 1));
		*((*avptra) + 1) = ft_strnew(0);
	}
	pipe(pipedfd);
	signal(SIGINT, ctrlhandlstdin);
	while (1)
	{
		ft_bzero(buff, BUFF_SIZE);
		ft_putstr("heredoc > ");
		if ((ret = getinputs(buff, NULL)) < 1 || !ft_strcmp(buff, *((*avptra) + 1)))
			break ;
		ft_putstr_fd(buff, pipedfd[1]);
		ft_putchar_fd('\n', pipedfd[1]);
	}
	signal(SIGINT, handler);
	close(pipedfd[1]);
	data->fd[0] = pipedfd[0];
	rmv_entries_in_avtable(avptra);
	return (0);
}

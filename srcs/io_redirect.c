/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchprogram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 01:07:27 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/25 14:38:29 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	rmv_entrie_in_avtable(char ***avptra)
{
	char	**avptrb;
	char	**avptrtmp;

	avptrb = (*avptra) + 1;
	free(*(*avptra));
	*(*avptra) = NULL;
	avptrtmp = *avptra;
	while (*avptrb)
	{
		*avptrtmp = *avptrb;
		*avptrb = NULL;
		avptrtmp++;
		avptrb++;
	}
}

static void	redir_from_to(t_execdata *data, char *a, char *b, int append)
{
	append = (append) ? O_APPEND : 0;
	if (b[0] == '&')
	{
		if (b[1] == '-')
			data->fd[ft_atoi(a)] = open("/dev/null", O_WRONLY);
		else
			data->fd[ft_atoi(a)] = ft_atoi((b + 1));
	}
	else
		data->fd[ft_atoi(a)] = open(b, O_CREAT | O_RDWR | O_TRUNC | append,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
}

static int	fd_redirect(t_execdata *data, char ***avptra)
{
	int		append;
	char	**part;

	append = (*(ft_strchr(**avptra, '>') + 1) == '>') ? O_APPEND : 0;
	part = ft_strsplit(**avptra, '>');
	if (!part || (***avptra != '>' && !part[1]))
		return (-1);
	if (part[0] && part[1] && !part[2])
	{
		if (ft_isnumber(part[0]))
			redir_from_to(data, part[0], part[1], append);
		else if (!ft_strcmp("&", part[0]))
		{
			redir_from_to(data, "1", part[1], append);
			data->fd[2] = data->fd[1];
		}
		else
			return (-1);
	}
	else if (part[0] && !part[1])
		redir_from_to(data, "1", part[0], append);
	ft_freetab(&part);
	rmv_entrie_in_avtable(avptra);
	return (0);
}

static int	inside_io_redirect(t_execdata *data, char ***avptr)
{
	if (!ft_strcmp(**avptr, ">") && *(*avptr + 1) != NULL)
		out_to_file(data, avptr, 0);
	else if (!ft_strcmp(**avptr, ">>") && *(*avptr + 1) != NULL)
		out_to_file(data, avptr, 1);
	else if (!ft_strcmp(**avptr, "<") && *(*avptr + 1) != NULL)
	{
		if (in_from_file(data, avptr) == -1)
			return (-1);
	}
	else if (!ft_strcmp(**avptr, "<<") && *(*avptr + 1) != NULL)
	{
		if (in_from_stdin(data, avptr) == -1)
			return (-1);
	}
	else if (ft_strchr(**avptr, '>'))
	{
		if (fd_redirect(data, avptr) == -1)
		{
			ft_putendl_fd("invalid fd redirection", 2);
			return (-1);
		}
	}
	return (0);
}

int			io_redirect(t_execdata *data, t_execdata *tmp)
{
	char	**avptr;
	int		ret;

	avptr = data->av;
	ret = 0;
	while (*avptr)
	{
		if ((ret = inside_io_redirect(data, &avptr)) == -1)
			return (-1);
		else if (ret == 0)
			avptr++;
	}
	if (tmp)
		ft_memcpy((char *)(tmp->fd), (char *)(data->fd), 3 * sizeof(int));
	return (1);
}

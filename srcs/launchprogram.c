/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchprogram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 01:07:27 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/22 18:53:10 by flagoutt         ###   ########.fr       */
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
		{
			printf("Redirecting %s to %s\n", part[0], part[1]);
			if (part[1][0] == '&')
			{
				if (part[1][1] == '-')
					data->fd[ft_atoi(part[0])] = open("/dev/null", O_WRONLY);
				else
					data->fd[ft_atoi(part[0])] = ft_atoi((part[1] + 1));
			}
			else
				data->fd[ft_atoi(part[0])] = open(part[1], O_CREAT | O_RDWR | O_TRUNC | append,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		}
		else if (!ft_strcmp("&", part[0]))
		{
			printf("Redirecting stdout & stderr to %s\n", part[1]);
			if (part[1][0] == '&')
			{
				if (part[1][1] == '-')
					data->fd[ft_atoi(part[0])] = open("/dev/null", O_WRONLY);
				else
					data->fd[1] = ft_atoi((part[1] + 1));
			}
			else
				data->fd[1] = open(part[1], O_CREAT | O_RDWR | O_TRUNC | append,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			data->fd[2] = data->fd[1];
		}
		else
			return (-1);
	}
	else if (part[0] && !part[1])
	{
		printf("Redirecting stdout to %s\n", part[0]);
		if (part[0][0] == '&')
		{
			if (part[0][1] == '-')
				data->fd[1] = open("/dev/null", O_WRONLY);
			else
				data->fd[1] = ft_atoi(part[0] + 1);
		}
		else
			data->fd[1] = open(part[0], O_CREAT | O_RDWR | O_TRUNC | append,
				   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	}
	ft_freetab(&part);
	rmv_entrie_in_avtable(avptra);
	return (0);
}

static int	io_redirect(t_execdata *data, t_execdata *tmp)
{
	char **avptr;

	avptr = data->av;
	while (*avptr)
	{
		if (!ft_strcmp(*avptr, ">") && *(avptr + 1) != NULL)
			out_to_file(data, &avptr, 0);
		else if (!ft_strcmp(*avptr, ">>") && *(avptr + 1) != NULL)
			out_to_file(data, &avptr, 1);
		else if (!ft_strcmp(*avptr, "<") && *(avptr + 1) != NULL)
		{
			if (in_from_file(data, &avptr) == -1)
				return (-1);
		}
		else if (!ft_strcmp(*avptr, "<<") && *(avptr + 1) != NULL)
		{
			if (in_from_stdin(data, &avptr) == -1)
				return (-1);
		}
		else if (ft_strchr(*avptr, '>'))
		{
			if (fd_redirect(data, &avptr) == -1)
			{
				ft_putendl_fd("invalid fd redirection", 2);
				return (-1);
			}
		}
		else
			avptr++;
	}
	if (tmp)
	{
		tmp->fd[0] = data->fd[0];
		tmp->fd[1] = data->fd[1];
		tmp->fd[2] = data->fd[2];
	}
	return (1);
}

int			launchprogram(t_execdata *data, t_execdata *tmp)
{
	pid_t	shell;
	int		ret;

	if (io_redirect(data, tmp) == -1)
		return (1);
	if (data->av[0] != NULL)
	{
		if ((ret = ((tmp != NULL) ? execbi(tmp->av[0], tmp) :
					execbi(data->av[0], data))) == 0)
		{
			shell = fork();
			if (shell > 0)
			{
				unsetallsignal();
		// PENSER A FAIRE LES || ET &&, waitpid(...)
				wait(&shell);
		// VOILA

				setallsignal();
			}
			else if (shell == 0 && childexec(data, tmp) == 1)
				return (0);
		}
		else if (ret == 2)
			return (2);
	}
	ft_freetab(&(data->av));
	return (1);
}

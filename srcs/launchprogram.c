/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchprogram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 01:07:27 by flagoutt          #+#    #+#             */
/*   Updated: 2016/02/12 17:37:57 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static int out_to_file(t_execdata *data, char ***avptra, int append)
{
	char **avptrb;
	char	**avptrtmp;

	append = (append) ? O_APPEND : 0;
	// OPEN 'file' AND FILL data->out AND tmp->out WITH ITS FD (dnt fget 2 close l8r)
	data->fd[1] = open(*((*avptra) + 1), O_CREAT | O_RDWR | append,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	// REMOVE ">" AND 'file' IN THE AV TABLE
	avptrb = (*avptra) + 2;
	free(*(*avptra));
	*(*avptra) = NULL;
	free(*((*avptra) + 1));
	*((*avptra) + 1) = NULL;
	avptrtmp = *avptra;
	while (*avptrb)
	{
		printf("(*avptra)zeub = %s\n", *avptrtmp);
		*avptrtmp = *avptrb;
		*avptrb = NULL;
		avptrtmp++;
		avptrb++;
	}
	return (0);
}

static int in_from_file(t_execdata *data, char ***avptra)
{
	char	**avptrb;
	char	**avptrtmp;
	int		fd;

	printf("Opening %s\n", *((*avptra) + 1));
	fd = open(*((*avptra) + 1), O_RDONLY);
	if (fd == -1)
	{
		ft_putstr("This file cannot be opened.\n");
		return (-1);
	}
	else
		data->fd[0] = fd;
	// REMOVE "<" AND 'file' IN THE AV TABLE
	avptrb = (*avptra) + 2;
	free(*(*avptra));
	*(*avptra) = NULL;
	free(*((*avptra) + 1));
	*((*avptra) + 1) = NULL;
	avptrtmp = *avptra;
	while (*avptrb)
	{
		printf("(*avptra)zeub = %s\n", *avptrtmp);
		*avptrtmp = *avptrb;
		*avptrb = NULL;
		avptrtmp++;
		avptrb++;
	}
	return (0);
}

static void ctrlhandlstdin(int signal)
{
	(void)signal;
	ft_putstr("\nheredoc > ");
}

static int in_from_stdin(t_execdata *data, char ***avptra)
{
	char	**avptrb;
	char	**avptrtmp;
	char	buff[BUFF_SIZE];
	int		pipedfd[2];
	int		ret;

	printf("Reading stdin until >%s<\n", *((*avptra) + 1));
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
		if ((ret = getinputs(buff, NULL)) < 1)
			break ;
		if (!ft_strcmp(buff, *((*avptra) + 1)))
			break ;
		ft_putstr_fd(buff, pipedfd[1]);
		ft_putchar_fd('\n', pipedfd[1]);
	}
	signal(SIGINT, handler);
	close(pipedfd[1]);
	data->fd[0] = pipedfd[0];

	// REMOVE "<" AND 'file' IN THE AV TABLE
	avptrb = (*avptra) + 2;
	free(*(*avptra));
	*(*avptra) = NULL;
	free(*((*avptra) + 1));
	*((*avptra) + 1) = NULL;
	avptrtmp = *avptra;
	while (*avptrb)
	{
		printf("(*avptra)zeub = %s\n", *avptrtmp);
		*avptrtmp = *avptrb;
		*avptrb = NULL;
		avptrtmp++;
		avptrb++;
	}
	return (0);
}

static int fd_redirect(t_execdata *data, char ***avptra)
{
	char	**avptrb;
	char	**avptrtmp;
	int		append;
	char	**part;

	append = (*(ft_strchr(**avptra, '>') + 1) == '>') ? O_APPEND : 0;
	part = ft_strsplit(**avptra, '>');
	if (!part)
		return (-1);
	if (part[0] && part[1] && !part[2])
	{
		printf("Redirecting %s to %s\n", part[0], part[1]);
		if (ft_isnumber(part[0]))
		{
			if (part[1][0] == '&')
				data->fd[ft_atoi(part[0])] = ft_atoi((part[1] + 1));
			else
			{
				data->fd[ft_atoi(part[0])] = open(part[1],
												O_CREAT | O_RDWR | append,
												S_IRUSR | S_IWUSR | S_IRGRP |
												S_IWGRP | S_IROTH | S_IWOTH);
			}
		}
		else
			return (-1);
	}
	else if (part[0] && !part[1])
	{
		data->fd[1] = ft_atoi(part[0]);
		printf("Redirecting stdin to %s\n", part[0]);
	}

	// REMOVE "*>*" IN THE AV TABLE
	avptrb = (*avptra) + 1;
	free(*(*avptra));
	*(*avptra) = NULL;
	avptrtmp = *avptra;
	while (*avptrb)
	{
		printf("(*avptra)zeub = %s\n", *avptrtmp);
		*avptrtmp = *avptrb;
		*avptrb = NULL;
		avptrtmp++;
		avptrb++;
	}
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
				perror("invalid fd redirection");
				return (-1);
			}
		}
		else if (ft_strchr(*avptr, '<'))
			;
		else
			avptr++;
	}
	avptr = data->av;
	while (*avptr)
		printf("avptr = %s\n", *avptr++);

	if (tmp)
	{
		tmp->fd[0] = data->fd[0];
		tmp->fd[1] = data->fd[1];
	}
	return (1);
}

int		launchprogram(t_execdata *data, t_execdata *tmp)
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
				if (data->fd[1] > 1)
					close(data->fd[1]);
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

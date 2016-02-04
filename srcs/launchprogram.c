/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchprogram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 01:07:27 by flagoutt          #+#    #+#             */
/*   Updated: 2016/02/04 06:46:02 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static int	io_redirect(t_execdata *data, t_execdata *tmp)
{
	char **avptra;
	char **avptrb;
//	char **avptrtmp;

	avptra = data->av;
	while (*avptra)
	{
		if (!ft_strcmp(*avptra, ">") && *(avptra + 1) != NULL)
		{
			// OPEN 'file' AND FILL data->out AND tmp->out WITH ITS FD (dnt fget 2 close l8r)
			data->fd[1] = open(*(avptra + 1), O_CREAT | O_RDWR,
							S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			if (tmp)
				tmp->fd[1] = data->fd[1];

			// REMOVE ">" AND 'file' IN THE AV TABLE
			avptrb = avptra + 2;
			free(*avptra);
			*avptra = NULL;
			free(*(avptra + 1));
			*(avptra + 1) = NULL;
			while (*avptrb)
			{
				printf("avptrazeub = %s\n", *avptra);
				*avptra = *avptrb;
				*avptrb = NULL;
				avptra++;
				avptrb++;
			}
		}			
		avptra++;
	}
	avptra = data->av;
	while (*avptra)
		printf("avptra = %s\n", *avptra++);
	return (1);
}

int		launchprogram(t_execdata *data, t_execdata *tmp)
{
	pid_t	shell;
	int		ret;

	io_redirect(data, tmp);
	if (data->av[0] != NULL)
	{
		if ((ret = ((tmp != NULL) ? execbi(tmp->av[0], tmp) :
					execbi(data->av[0], data))) == 0)
		{
			shell = fork();
			if (shell > 0)
			{
				unsetallsignal();
				wait(&shell);
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

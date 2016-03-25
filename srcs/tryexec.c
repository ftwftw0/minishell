/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tryexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 13:34:14 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/25 14:00:01 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	close_fds(t_execdata *data)
{
	if (data->fd[1] != 1)
	{
		if (data->fd[1] != 2 && close(data->fd[1]) == -1)
			perror("close pipestdout");
		data->fd[1] = 1;
	}
	if (data->fd[2] != 2)
	{
		if (data->fd[2] != 1 && close(data->fd[2]) == -1)
			perror("close pipestdout");
		data->fd[2] = 2;
	}
	if (data->fd[0] != 0)
	{
		if (data->fd[0] != 1 && close(data->fd[0]) == -1)
			perror("close pipestdin");
		data->fd[0] = 0;
	}
}

void		tryexec(const char *path, t_execdata *data)
{
	if (data->fd[1] != 1)
	{
		if (dup2(data->fd[1], 1) == -1)
			perror("dup2 stdout");
	}
	if (data->fd[2] != 2)
	{
		if (dup2(data->fd[2], 2) == -1)
			perror("dup2 stdout");
	}
	if (data->fd[0] != 0)
	{
		if (dup2(data->fd[0], 0) == -1)
			perror("dup2 du stdin");
	}
	close_fds(data);
	execve(path, data->av, data->env);
}

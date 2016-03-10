/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 17:00:39 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/10 17:45:30 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	tryexec(const char *path, t_execdata *data)
{
	if (data->fd[2] != 2)
	{
		if (dup2(data->fd[2], 2) == -1)
			perror("dup2 stdout");
		if (close(data->fd[2]) == -1)
			perror("close pipestdout");
		data->fd[2] = 2;
	}
	if (data->fd[1] != 1)
	{
		if (dup2(data->fd[1], 1) == -1)
			perror("dup2 stdout");
		if (close(data->fd[1]) == -1)
			perror("close pipestdout");
		data->fd[1] = 1;
	}
	if (data->fd[0] != 0)
	{
		if (dup2(data->fd[0], 0) == -1)
			perror("dup2 du stdin");
		if (close(data->fd[0]) == -1)
			perror("close pipestdin");
		data->fd[0] = 0;
	}
	execve(path, data->av, data->env);
}

static void	intopaths(t_execdata *data, t_execdata *tmp)
{
	char	*strpaths;
	char	**paths;
	int		i;

	if ((strpaths = ft_getenv(data->env, "PATH")) != NULL)
	{
		paths = ft_strsplit(strpaths, ':');
		i = -1;
		if (tmp)
			data = tmp;
		while (paths[++i])
		{
			free(strpaths);
			strpaths = ft_strtrijoin(paths[i], "/", data->av[0]);
			tryexec(strpaths, data);
			free(paths[i]);
		}
		free(paths);
		free(strpaths);
	}
	tryexec(data->av[0], data);
}

static void	abspath(t_execdata *data, t_execdata *tmp)
{
	char *path;
	char *pwd;

	if ((pwd = ft_getenv(data->env, "PWD")))
	{
		free(pwd);
		if (tmp)
		{
			if (tmp->av[0][0] == '/')
				path = ft_strjoin(pwd, tmp->av[0]);
			else
				path = ft_strjoin(pwd, tmp->av[0] + 1);
			tryexec(path, tmp);
		}
		else
		{
			if (data->av[0][0] == '/')
				path = ft_strjoin(pwd, data->av[0]);
			else
				path = ft_strjoin(pwd, data->av[0] + 1);
			tryexec(path, data);
		}
		free(path);
	}
	tryexec(data->av[0], data);
}

static void	homepath(t_execdata *data, t_execdata *tmp)
{
	char *buff;
	char *home;

	if ((home = ft_getenv(data->env, "HOME")) != NULL)
	{
		if (tmp)
		{
			if (home[ft_strlen(home) - 1] == '/')
				home[ft_strlen(home) - 1] = '\0';
			buff = ft_strjoin(home, data->av[0] + 1);
			tryexec(buff, tmp);
		}
		else
		{
			if (home[ft_strlen(home) - 1] == '/')
				home[ft_strlen(home) - 1] = '\0';
			buff = ft_strjoin(home, data->av[0] + 1);
			tryexec(buff, data);
		}
		free(home);
		free(buff);
	}
	else
		ft_putendl_fd("cd: no HOME environment variable.", 2);
}

int			childexec(t_execdata *data, t_execdata *tmp)
{
	if (tmp)
	{
		if ((tmp->av[0][0] == '/' || tmp->av[0][0] == '.') &&
			ft_strncmp(tmp->av[0], "/Volumes", 8) &&
			ft_strncmp(tmp->av[0], "/nfs", 4))
			abspath(data, tmp);
		else if (tmp->av[0][0] == '~')
			homepath(data, tmp);
		else
			intopaths(data, tmp);
	}
	else
	{
		if ((data->av[0][0] == '/' || data->av[0][0] == '.') &&
			ft_strncmp(data->av[0], "/Volumes", 8) &&
			ft_strncmp(data->av[0], "/nfs", 4))
			abspath(data, tmp);
		else if (data->av[0][0] == '~')
			homepath(data, tmp);
		else
			intopaths(data, tmp);
	}
	ft_putstr_fd("Program cannot be launched.\n", 2);
	return (1);
}

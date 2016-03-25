/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 17:00:39 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/25 13:35:52 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

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

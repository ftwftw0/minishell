/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 16:58:09 by flagoutt          #+#    #+#             */
/*   Updated: 2017/02/03 01:22:46 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

char		*gethomepath(char *buff)
{
	char *home;

	if ((home = ft_getenv(g_env, "HOME")) != NULL)
	{
		if (home[ft_strlen(home) - 1] == '/')
			home[ft_strlen(home) - 1] = '\0';
		ft_memmove(buff, &buff[ft_strlen(home) - 1], ft_strlen(buff));
		ft_strcpy(buff, home);
		free(home);
	}
	return (buff);
}

static void	execunsetenv(t_execdata *data)
{
	int i;

	i = 1;
	while (data->av[i])
	{
		ft_unsetenv(data, data->av[i]);
		i++;
	}
}

static void	execsetenv(t_execdata *data)
{
	char	*buff;
	char	*ptr;
	int		i;

	i = 1;
	while (data->av[i] && (ptr = ft_strchr(data->av[i], '=')))
	{
		buff = ft_strndup(data->av[i], ptr - data->av[i]);
		ft_setenv(data, buff, ptr + 1, 1);
		free(buff);
		i++;
	}
	if (i == 1)
		ft_env(data);
	else if (!ptr)
		ft_putendl_fd("Bad environment variable format.\
		(use: setenv VAR=VALUE) [...]", 2);
}

static int	execbi_split(char *str, t_execdata *data, int i)
{
	if (!ft_strcmp(str, "echo"))
	{
		if (!ft_strcmp(data->av[1], "-n"))
			i++;
		while (data->av[i])
		{
			ft_putstr_fd(data->av[i++], data->fd[1]);
			if (data->av[i])
				ft_putchar_fd(' ', data->fd[1]);
		}
		if (ft_strcmp(data->av[1], "-n"))
			ft_putchar_fd('\n', data->fd[1]);
	}
	else if (!ft_strcmp(str, "exit"))
	{
		ft_goodbye();
		if (data->av[1] && ft_isnumber(data->av[1]))
			i = ft_atoi(data->av[1]);
		ft_deinit(data, NULL);
		exit(i);
	}
	else
		return (0);
	return (1);
}

int			execbi(char *str, t_execdata *data)
{
	if (!ft_strcmp(str, "env"))
		ft_env(data);
	else if (!ft_strcmp(str, "export") ||
			!ft_strcmp(str, "setenv"))
		execsetenv(data);
	else if (!ft_strcmp(str, "unsetenv"))
		execunsetenv(data);
	else if (!ft_strcmp(str, "cd"))
		ft_cd(data);
	else if (!ft_strcmp(str, "pid"))
	{
		ft_putnbr(getpid());
		ft_putchar('\n');
	}
	else if (execbi_split(str, data, 1) == 0)
		return (0);
	return (1);
}

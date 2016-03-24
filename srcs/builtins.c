/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 16:58:09 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/24 08:54:05 by flagoutt         ###   ########.fr       */
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
	else if (!ft_strcmp(str, "exit"))
	{
		ft_goodbye();
		ft_deinit(data, NULL);
		exit(0);
	}
	else
		return (0);
	return (1);
}

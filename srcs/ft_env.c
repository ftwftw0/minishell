/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 17:56:41 by flagoutt          #+#    #+#             */
/*   Updated: 2017/01/31 21:01:09 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static char	**mknewav(char **av, int i)
{
	char	**new;
	int		j;

	j = 0;
	while (av[j])
		j++;
	new = (char **)malloc(sizeof(char *) * (j - i + 1));
	j = 0;
	while (av[i])
	{
		new[j++] = ft_strdup(av[i]);
		i++;
	}
	new[j] = NULL;
	return (new);
}

static void	ft_envsplitted(t_execdata *data, t_execdata *tmp, int i)
{
	char		*buff;
	char		*ptr;

	while (data->av[i] && (ptr = ft_strchr(data->av[i], '=')))
	{
		buff = ft_strndup(data->av[i], ptr - data->av[i]);
		ft_setenv(tmp, buff, ptr + 1, 1);
		free(buff);
		i++;
	}
	tmp->av = mknewav(data->av, i);
	if ((i = launchprogram(data, tmp)) == 0 || i == 2)
	{
		exit(0);
	}
}

int			ft_env(t_execdata *data)
{
	t_execdata	*tmp;
	int			i;

	i = 1;
	if (data->av[1] == NULL)
		showstringtab(data->env);
	else if (!ft_strcmp(data->av[1], "-i") && data->av[2])
	{
		tmp = (t_execdata *)malloc(sizeof(t_execdata));
		tmp->fd[0] = data->fd[0];
		tmp->fd[1] = data->fd[1];
		if (!ft_strcmp(data->av[i], "-i"))
		{
			tmp->env = (char **)malloc(sizeof(char *) * (i++));
			tmp->env[0] = NULL;
		}
		else
			tmp->env = ft_tabstrdup(data->env);
		ft_envsplitted(data, tmp, i);
	}
	return (1);
}

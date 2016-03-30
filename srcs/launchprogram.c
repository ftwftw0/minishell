/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launchprogram.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 14:37:26 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/30 08:45:27 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static void	parent_process(pid_t *shell)
{
	wait(shell);
	terminit();
	setallsignal();
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
			unsetallsignal();
			termdeinit();
			shell = fork();
			if (shell > 0)
				parent_process(&shell);
			else if (shell == 0 && childexec(data, tmp) == 1)
				return (0);
		}
		else if (ret == 2)
			return (2);
	}
	ft_freetab(&(data->av));
	return (1);
}

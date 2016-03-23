/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/24 16:00:48 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/23 07:24:33 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

char	*ft_getenv(char **env, char *elem)
{
	char	*uppername;
	char	*ptr;
	char	*value;
	int		i;
	int		len;

	i = -1;
	value = NULL;
	len = ft_strlen(elem);
	uppername = ft_strdup(elem);
	ft_strupper(uppername);
	while (env[++i])
		if ((ptr = ft_strchr(env[i], '=')) &&
			ptr - env[i] == (long)ft_strlen(elem) &&
			(!ft_strncmp(env[i], elem, ptr - env[i]) ||
			 !ft_strncmp(env[i], uppername, ptr - env[i])))
			value = ft_strndup(ptr + 1, ft_strlen(ptr));
	free(uppername);
	return (value);
}

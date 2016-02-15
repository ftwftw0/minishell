/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_str_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 15:49:45 by flagoutt          #+#    #+#             */
/*   Updated: 2016/02/15 11:33:45 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static char			**tabrealloc(char **strtab, int tabsize)
{
	char **newtab;

	newtab = (char **)malloc(sizeof(char *) * (tabsize + 2));
	tabsize = -1;
	while (strtab[++tabsize])
		newtab[tabsize] = strtab[tabsize];
	newtab[tabsize] = NULL;
	newtab[tabsize + 1] = NULL;
	free(strtab);
	return (newtab);
}

int					add_str_to_tab(char ***strtab, const char *str)
{
	int tablen;
	
	tablen = ft_tablen(*strtab);
	*strtab = tabrealloc(*strtab, tablen);
	(*strtab)[tablen] = ft_strdup(str);
	return (1);
}

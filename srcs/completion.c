/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/11 19:53:47 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/23 02:43:03 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static t_elem	*ft_createlem(char *name, int size, t_elem *prev, t_elem *next)
{
	t_elem *elem;

	elem = (t_elem *)malloc(sizeof(t_elem));
	elem->name = ft_strdup(name);
	elem->size = size;
	elem->prev = prev;
	elem->next = next;
	return (elem);
}

static t_elem	*ft_creatlist(char *buff)
{
	struct dirent	*pwd;
	t_elem			*list;
	t_elem			*tmp;
	DIR				*fd;

	list = NULL;
	if (!(fd = opendir(".")))
		return (NULL);
	(ft_strncmp(buff, "./", 2) == 0) ? buff = buff + 2 : 0;
	while (list == NULL && (pwd = readdir(fd)))
		if (ft_strnequ(buff, pwd->d_name, ft_strlen(buff)))
			list = ft_createlem(pwd->d_name, ft_strlen(pwd->d_name), 0, 0);
	tmp = list;
	while ((pwd = readdir(fd)))
		if (ft_strnequ(buff, pwd->d_name, ft_strlen(buff)))
		{
			tmp->next = ft_createlem(pwd->d_name, ft_strlen(pwd->d_name),
										tmp, NULL);
			tmp = tmp->next;
		}
	closedir(fd);
	return (list);
}

static void		completionnext(t_elem *list, char *tmp, char *buff, char **ptr)
{
	char	*ptrr;

	if (list->next == NULL)
	{
		(!ft_strncmp(tmp, "./", 2)) ? ft_strcpy(tmp + 2, list->name) :
										ft_strcpy(tmp, list->name);
		tmp = tgetstr("le", NULL);
		while (
		tputs(tmp, 1, custom_putchar);
	}
	else if ((ptrr = ft_select(list)))
	{
		if (ft_strncmp(tmp, "./", 2) == 0)
			ft_strcpy(tmp + 2, ptrr);
		else
			ft_strcpy(tmp, ptrr);
	}
	(*ptr) = &(buff[ft_strlen(buff)]);
}

void			completion(char *buff, char **ptr)
{
	t_elem	*list;
	char	*ptrr;
	char	*tmp;
	char	yebuf[BUFF_SIZE];

	ptrr = buff;
	tmp = buff;
	while ((ptrr = ft_strchr(ptrr + 1, ' ')))
		tmp = ptrr + 1;
	if ((list = ft_creatlist(tmp)))
	{
		completionnext(list, tmp, buff, ptr);
		showprompt(getcwd(yebuf, BUFF_SIZE));
		ft_putstr(buff);
	}
}

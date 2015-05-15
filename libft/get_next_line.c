/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 16:20:34 by flagoutt          #+#    #+#             */
/*   Updated: 2015/03/09 15:55:15 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_readfile(char **str, int fd)
{
	char	*buff;
	char	*tmpstr;
	int		ret;
	int		strsize;

	strsize = 0;
	buff = ft_strnew(BUFF_SIZE);
	if (!buff)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		if (ft_strlen(buff) != (unsigned int)ret)
			return (-1);
		strsize += ret;
		tmpstr = ft_strdup(*str);
		*str = ft_strjoin(tmpstr, buff);
	}
	free(buff);
	if (ret < 0)
		return (-1);
	return (strsize);
}

int		ft_testdata(t_gnldata *data, char **line, int fd)
{
	int i;

	i = 0;
	line = line;
	data->fd = fd;
	if (!(*data).nbline)
		(*data).nbline = 0;
	if (!(*data).fileended)
		(*data).fileended = 0;
	if (!(*data).txtsize)
		(*data).txtsize = 0;
	if ((*data).fileended == 1)
		return (0);
	if (!(*data).text)
		(*data).text = ft_strnew(1);
	if ((i = ft_readfile(&((*data).text), fd)) > 0)
		(*data).txtsize = i;
	if (i == -1)
		return (0);
	return (1);
}

int		ft_gnl(int fd, char **line, t_gnldata *data)
{
	int					i;
	char				*ptr;

	i = 0;
	if (!ft_testdata(data, line, fd))
		return (-1);
	ptr = data->text;
	i = 0;
	while (ptr != NULL && i++ < (int)data->nbline)
		ptr = ft_strchr(ptr, '\n') + 1;
	i = 0;
	if (!ptr)
		ptr = data->text;
	while (ptr[i] != '\n' && ptr[i])
		i++;
	*line = ft_strsub(ptr, 0, i);
	data->nbline++;
	if (&ptr[i] - (char*)(data->text) >= data->txtsize || i == data->txtsize)
	{
		free(data->text);
		data->fileended = 1;
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_gnldata	*data = NULL;
	t_gnldata			*tmp;

	if (data == NULL)
	{
		data = (t_gnldata *)malloc(sizeof(t_gnldata));
		data->fd = fd;
		return (ft_gnl(fd, line, data));
	}
	else
	{
		tmp = data;
		while (tmp->next != NULL)
		{
			if (tmp->fd == fd)
				break ;
			tmp = tmp->next;
		}
		if (tmp->next == NULL && tmp->fd != fd)
		{
			tmp->next = (t_gnldata *)malloc(sizeof(t_gnldata));
			tmp = tmp->next;
		}
		return (ft_gnl(fd, line, tmp));
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_redirections.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/09 14:45:47 by flagoutt          #+#    #+#             */
/*   Updated: 2016/03/09 18:36:01 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

static int out_to_file(t_execdata *data, char ***avptra, int append)
{
    char **avptrb;
    char    **avptrtmp;

    append = (append) ? O_APPEND : 0;
    // OPEN 'file' AND FILL data->out AND tmp->out WITH ITS FD (dnt fget 2 close l8r)
    data->fd[1] = open(*((*avptra) + 1), O_CREAT | O_RDWR | append,
					   S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    // REMOVE ">" AND 'file' IN THE AV TABLE
    avptrb = (*avptra) + 2;
    free(*(*avptra));
    *(*avptra) = NULL;
    free(*((*avptra) + 1));
    *((*avptra) + 1) = NULL;
    avptrtmp = *avptra;
    while (*avptrb)
    {
        printf("(*avptra)zeub = %s\n", *avptrtmp);
        *avptrtmp = *avptrb;
        *avptrb = NULL;
        avptrtmp++;
        avptrb++;
    }
    return (0);
}

static int in_from_file(t_execdata *data, char ***avptra)
{
    char    **avptrb;
    char    **avptrtmp;
    int     fd;

    printf("Opening %s\n", *((*avptra) + 1));
    fd = open(*((*avptra) + 1), O_RDWR);
    if (fd == -1)
    {
        ft_putstr("This file cannot be opened.\n");
        return (-1);
    }
    else
        data->fd[0] = fd;
    // REMOVE "<" AND 'file' IN THE AV TABLE
    avptrb = (*avptra) + 2;
    free(*(*avptra));
    *(*avptra) = NULL;
    free(*((*avptra) + 1));
    *((*avptra) + 1) = NULL;
    avptrtmp = *avptra;
    while (*avptrb)
    {
        printf("(*avptra)zeub = %s\n", *avptrtmp);
        *avptrtmp = *avptrb;
        *avptrb = NULL;
        avptrtmp++;
        avptrb++;
    }
    return (0);
}

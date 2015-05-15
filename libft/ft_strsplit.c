/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 14:54:30 by flagoutt          #+#    #+#             */
/*   Updated: 2015/01/14 16:07:37 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitsplitted(char const *s, char c, char **tab)
{
	int		size;
	char	*ptr;
	int		i;
	int		words;

	size = 0;
	ptr = NULL;
	words = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		ptr = (char *)&s[i];
		while (s[i] != c && s[i])
		{
			i++;
			size++;
		}
		tab[words++] = ft_strsub(ptr, 0, size);
		size = 0;
	}
	return (tab);
}

char	**ft_strsplit(char const *s, char c)
{
	char			**tab;
	int				words;
	unsigned int	i;

	if (!s || !c)
		return (NULL);
	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			words++;
		while (s[i] != c && s[i])
			i++;
	}
	tab = (char **)malloc(sizeof(char*) * (words + 1));
	if (!tab)
		return (NULL);
	i = 0;
	tab = ft_splitsplitted(s, c, tab);
	tab[words] = NULL;
	return (tab);
}

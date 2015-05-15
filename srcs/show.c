/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/23 16:38:42 by flagoutt          #+#    #+#             */
/*   Updated: 2015/05/15 14:53:51 by flagoutt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh1.h"

int		showprompt(char *currentdir)
{
	ft_triputstr("\033[33m[", currentdir, "]\033[35m$\033[0m ");
	return (1);
}

int		showstringtab(char **strtab)
{
	int i;

	i = 0;
	if (!strtab)
		return (0);
	while (strtab[i])
		ft_putendl(strtab[i++]);
	return (1);
}

void	ft_welcome(void)
{
	ft_putstr("\033[43m\033[30m");
	ft_putendl("                                                            ");
	ft_putendl("       ___                  ____                  ___       ");
	ft_putendl("  ____(   \\              .-'    `-.              /   )____  ");
	ft_putendl(" (____     \\_____       /  (O  O)  \\       _____/     ____)");
	ft_putendl("(____            `-----(      )     )-----'            ____)");
	ft_putendl(" (____     _____________\\  \\____/  /_____________     ____)");
	ft_putendl("   (______/              `-.____.-'              \\______)   ");
	ft_putendl("                                                            ");
	ft_putstr("\033[37m\033[40m");
	ft_putstr("\033[0m\n");
}

void	ft_goodbye(void)
{
	ft_putchar('\n');
	ft_putstr("\033[43m\033[30m        CHECK ME OUT I CAN BEAT OFF");
	ft_putendl("AND PLAY GRAND THEFT                     ");
	ft_putendl("       AUTO AT ONCE (BUT NOT MUCH ELSE REALLY)             ");
	ft_putendl("                         _                                 ");
	ft_putendl("                       .(_)_                               ");
	ft_putendl("                      /,    \\                 .            ");
	ft_putendl("                     <_)   (\\                             ");
	ft_putendl("                    __/._ .-|/_         `     .     '      ");
	ft_putendl("                     (   .   )             .  |  .         ");
	ft_putendl("                     : .d8b-'/       _      \\.-./      _   ");
	ft_putendl(" a:f.-.-..-.--.--._  ( ( Y `n   ____________'...`__________");
	ft_putendl(" '/    '-.  . -      : : # .v       .    ----==-----    .  ");
	ft_putendl("    .'-.   ' .-,_.-' ( )_#_/  `-._.   -     ---     --     ");
	ft_putendl("           ._.-'      O/ #        `/:_      ---  -         ");
	ft_putendl("   '.,   .-'          \"' #          ` `=. .  -             ");
	ft_putendl("     _.-'                #               `-:               ");
	ft_putendl("                         .                                 ");
	ft_putendl("                         `:                                ");
	ft_putendl("                          '                                ");
	ft_putstr("\033[37m\033[40m");
	ft_putstr("\033[0m\n");
}

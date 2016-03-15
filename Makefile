#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flagoutt <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/05 17:59:57 by flagoutt          #+#    #+#              #
#    Updated: 2016/03/15 15:21:57 by flagoutt         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# **************************************************************************** #
# 		PROGRAM																   #
# **************************************************************************** #
NAME		=	21sh

# **************************************************************************** #
#		SOURCES
# **************************************************************************** #

DIRSRC		=	srcs
DIRSLCT		=	srcs

SRCS = 	$(DIRSLCT)/inits.c \
        $(DIRSLCT)/deinit.c \
        $(DIRSLCT)/freelist.c \
        $(DIRSLCT)/ft_mklist.c \
        $(DIRSLCT)/ft_select.c \
        $(DIRSLCT)/putselecteds.c \
        $(DIRSLCT)/showslct.c \
        $(DIRSLCT)/keyhooks.c \
        $(DIRSLCT)/mvcursorslct.c \
        $(DIRSLCT)/cleanterm.c \
		$(DIRSRC)/show.c \
		$(DIRSRC)/copystringtab.c \
		$(DIRSRC)/builtins.c \
		$(DIRSRC)/ft_env.c \
		$(DIRSRC)/ft_cd.c \
		$(DIRSRC)/ft_deinit.c \
		$(DIRSRC)/ft_setenv.c \
		$(DIRSRC)/ft_unsetenv.c \
		$(DIRSRC)/ft_getenv.c \
		$(DIRSRC)/ft_exec.c \
		$(DIRSRC)/getinputs.c \
		$(DIRSRC)/signalhandler.c \
		$(DIRSRC)/init.c \
		$(DIRSRC)/customputchar.c \
		$(DIRSRC)/mvcursor.c \
		$(DIRSRC)/mvcursor_tools.c \
		$(DIRSRC)/mvcursor_tools2.c \
		$(DIRSRC)/completion.c \
		$(DIRSRC)/handlers.c \
		$(DIRSRC)/launchprogram.c \
		$(DIRSRC)/add_str_to_tab.c \
		$(DIRSRC)/copycutpaste.c \
		$(DIRSRC)/pipedcommands.c \
		$(DIRSRC)/fd_redirections.c \
		main.c

# **************************************************************************** #
#		DIRECTORIES
# **************************************************************************** #

DIRBIN		=	bin
BIN			=	$(addprefix $(DIRBIN)/, $(SRCS:.c=.o))
DIRLIST		=	srcs
DIRINC		=	./includes/
DIRINC_FT	=	./libft/
DIRINC_SELECT	=	./ft_select/includes/

# **************************************************************************** #
#		COMPILE
# **************************************************************************** #

CC			=	gcc -g
CFLAG		=	-Wall -Wextra -Werror
INCS		=	-I$(DIRINC) -I$(DIRINC_FT) -I$(DIRINC_SELECT)
LIBS		=   -Llibft/ -lft -ltermcap

# **************************************************************************** #
#		RULES																   #
# **************************************************************************** #

all: libft $(NAME)

libft:
	@$(MAKE) -C libft

$(NAME): $(DIRBIN) $(BIN)
	@printf " ------------------------------------------------------------ \n"
	@$(CC) $(CFLAG) $(BIN) $(LIBS) -o $(NAME)
	@printf "\n\t\tMAKING PROJECT\t\t\t"
	@printf "\t\e[32m[DONE]\e[0m\n\n"
	@printf " ------------------------------------------------------------ \n"

$(addprefix $(DIRBIN)/, %.o) : %.c $(DIRINC) $(DIRINC_FT)
	@mkdir -p $(@D)
	@printf "compiling \e[33m%-41s\e[0m" "$@..."
	@$(CC) $(CFLAG) $(INCS) -o $@ -c $<
	@printf "\t\e[32m[DONE]\e[0m\n"

$(DIRBIN) :
	@/bin/mkdir $(DIRBIN); \
		for DIR in $(DIRLIST); \
		do \
		/bin/mkdir $(DIRBIN)/$$DIR; \
		done

clean:
	@$(MAKE) -C libft $@
	@printf " ------------------------------------------------------------ \n"
	@printf "cleaning binaries...\t\t\t\t\t"
	@/bin/rm -rf $(DIRBIN);
	@printf "\e[32m[DONE]\e[0m\n"

fclean: clean
	@$(MAKE) -C libft $@
	@printf " ------------------------------------------------------------ \n"
	@printf "cleaning project...\t\t\t\t\t"
	@/bin/rm -rf $(NAME);
	@printf "\e[32m[DONE]\e[0m\n"
	@printf " ------------------------------------------------------------ \n"

re: fclean all

.PHONY: clean fclean re libft

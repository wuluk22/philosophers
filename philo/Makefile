# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clegros <clegros@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 19:08:47 by clegros           #+#    #+#              #
#    Updated: 2024/04/16 19:08:50 by clegros          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
SRC		= src/ft_dinner.c\
			src/ft_get_set.c\
			src/ft_init.c\
			src/ft_monitor.c\
			src/ft_parsing.c\
			src/ft_philo.c\
			src/ft_safe.c\
			src/ft_sync_utils.c\
			src/ft_utils.c
OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -Iincludes/ -Isrc/
COMP	= $(CC) $(CFLAGS)
RM		= rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
			$(COMP) $(OBJ) -o $@ -lpthread

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJ) $(NAME)

fclean: clean
			$(RM) $(NAME)

re:		fclean all

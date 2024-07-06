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
SRC		= includes/philo.c\
			includes/ft_routine.c\
			includes/ft_utils.c
OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -Iincludes/
COMP	= $(CC) $(CFLAGS)
RM		= rm -f

all:	$(NAME)

$(NAME):	$(OBJ)
			$(COMP) -fsanitize=address -g3 $(OBJ) -o $@ -lpthread

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			$(RM) $(OBJ) $(NAME)

fclean: clean
			$(RM) $(NAME)

re:		fclean all

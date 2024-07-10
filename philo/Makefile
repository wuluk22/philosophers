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
SRC		= includes/ft_clean.c\
		  	includes/ft_data.c\
			includes/ft_dead.c\
			includes/ft_get_set.c\
			includes/ft_init.c\
			includes/ft_parsing.c\
			includes/ft_philo.c\
			includes/ft_print.c\
			includes/ft_safe.c\
			includes/ft_sync_utils.c\
			includes/ft_utils.c
OBJ		= $(SRC:.c=.o)
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -Iincludes/
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

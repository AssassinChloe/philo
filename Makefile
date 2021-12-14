# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 13:27:24 by cassassi          #+#    #+#              #
#    Updated: 2021/12/08 15:32:43 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= philo.c ft_atoi.c time.c lifeanddeathofaphilosopher.c display.c

OBJSD	= .obj/

OBJS	= $(addprefix $(OBJSD), $(SRCS:%.c=%.o))

INC		= -I philo.h

CC		= clang

FLAGS	= -Wall -Wextra -Werror -fsanitize=address

all :		$(NAME)

$(NAME) :	$(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(FLAGS)

clean :
				rm -rf $(OBJSD)

fclean :	clean
				rm -f $(NAME)

re :		fclean all

$(OBJSD)%.o:%.c
		@mkdir -p $(OBJSD)
		$(CC) $(INC) -o $@ -c $<

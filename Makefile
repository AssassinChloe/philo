# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 13:27:24 by cassassi          #+#    #+#              #
#    Updated: 2022/01/07 15:36:45 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= philo.c ft_atoi.c time.c lifeanddeathofaphilosopher.c display.c\
  	  init.c ending.c check_vitals.c

OBJSD	= .obj/

OBJS	= $(addprefix $(OBJSD), $(SRCS:%.c=%.o))

INC	= -I philo.h

CC	= clang

FLAGS	= -pthread -Wall -Wextra -Werror

all :		$(NAME)

$(NAME) :	$(OBJS)
				$(CC) $(FLAGS) -o $(NAME) $(OBJS) 

clean :
				rm -rf $(OBJSD)

fclean :	clean
				rm -f $(NAME)

re :		fclean all

$(OBJSD)%.o:%.c
		@mkdir -p $(OBJSD)
		$(CC) $(FLAGS) $(INC) -o $@ -c $<

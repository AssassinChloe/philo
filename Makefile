# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cassassi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/03 13:27:24 by cassassi          #+#    #+#              #
#    Updated: 2021/12/22 17:36:00 by cassassi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= philo.c ft_atoi.c time.c lifeanddeathofaphilosopher.c display.c puttext.c\
  	  init.c ending.c

BONUS	= philo_bonus

BDIR	= bonus/

BFILE	= philo_bonus.c ft_atoi_bonus.c time_bonus.c lifeanddeathofaphilosopher_bonus.c display_bonus.c puttext_bonus.c\
  	  init_bonus.c ending_bonus.c

BSRCS	= $(addprefix $(BDIR), $(BFILE))

OBJSD	= .obj/

OBJS	= $(addprefix $(OBJSD), $(SRCS:%.c=%.o))

BOBJS	= $(BSRCS:%.c=%.o)

INC	= -I philo.h

BINC	= -I bonus/philo_bonus.h

CC	= clang

FLAGS	= -pthread -Wall -Wextra -Werror

all :		$(NAME)

$(NAME) :	$(OBJS)
				$(CC) -o $(NAME) $(OBJS) $(FLAGS)

clean :
				rm -rf $(OBJSD)
				rm -rf $(BOBJS)

fclean :	clean
				rm -f $(NAME)
				rm -f $(BONUS)

re :		fclean all

rebonus :	fclean bonus

bonus :		$(BOBJS)
				$(CC) -o $(BONUS) $(BOBJS) $(FLAGS)

$(OBJSD)%.o:%.c
		@mkdir -p $(OBJSD)
		$(CC) $(INC) -o $@ -c $<

$(BOBJSD)%.o:%.c
		$(CC) $(BINC) -o $@ -c $<

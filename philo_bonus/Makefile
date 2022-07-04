# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/03 16:05:20 by jcalon            #+#    #+#              #
#    Updated: 2022/07/04 10:57:51 by jcalon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo_bonus

SRCS 	= srcs/philo_bonus.c srcs/utils_bonus.c srcs/check_bonus.c srcs/eat_think_sleep_bonus.c

OBJS 	= ${SRCS:.c=.o}

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -pthread -g

INCLUDES = -I includes

.c.o:
		@${CC} ${CFLAGS} ${INCLUDES} -c -o $@ $<

all: 	${NAME}

${NAME}: ${OBJS}
		@$(CC) $(CFLAGS) ${OBJS} ${INCLUDES} -o ${NAME}
		@echo "\033[32mPhilo_bonus compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

clean:
		@rm -f ${OBJS}

fclean: clean
		@rm -f $(NAME)
		@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re:		fclean all

.PHONY: all clean fclean re
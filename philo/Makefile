# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/03 16:05:20 by jcalon            #+#    #+#              #
#    Updated: 2022/07/04 10:58:01 by jcalon           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS 	= srcs/philo.c srcs/utils.c srcs/status.c srcs/eat_think_sleep.c srcs/time.c

OBJS 	= ${SRCS:.c=.o}

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -pthread

INCLUDES = -I includes

.c.o:
		@${CC} ${CFLAGS} ${INCLUDES} -c -o $@ $<

all: 	${NAME}

${NAME}: ${OBJS}
		@$(CC) $(CFLAGS) ${OBJS} ${INCLUDES} -o ${NAME}
		@echo "\033[32mPhilo compiled! ᕦ(\033[31m♥\033[32m_\033[31m♥\033[32m)ᕤ\n"

clean:
		@rm -f ${OBJS}

fclean: clean
		@rm -f $(NAME)
		@echo "\n\033[31mDeleting EVERYTHING! ⌐(ಠ۾ಠ)¬\n"

re:		fclean all

.PHONY: all clean fclean re
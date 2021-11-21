# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/17 22:23:55 by amanchon          #+#    #+#              #
#    Updated: 2020/11/17 22:53:33 by amanchon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror -lpthread #-fsanitize=thread -g3

SRCS =			./main.c \
				./ecg.c \
				./ft_isdigit.c \
				./ft_putstr_fd.c \
				./init.c\
				./manger.c \
				./philo_ecrire.c\
				./ft_atoll.c \
				./ft_putnbr_fd.c \
				./ft_strlen.c \
				./mtn.c \
				./vie_philo.c \
				./creer_philo.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
	gcc -o $(NAME) $(OBJS) ${CFLAGS}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

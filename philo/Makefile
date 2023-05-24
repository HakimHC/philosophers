# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/14 23:52:05 by hakahmed          #+#    #+#              #
#    Updated: 2023/05/17 14:29:25 by hakim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -Wall -Werror -Wextra

CFLAGS += -g3

CFLAGS += -O3

CFLAGS += -I $(INC)

INC = inc

LDFLAGS = -pthread

# LDFLAGS += -fsanitize=thread

SRCDIR = src

SRCFILES = main.c \
	   utils.c \
	   time_utils.c

SRC = $(addprefix $(SRCDIR)/,$(SRCFILES))

OBJ = $(SRC:.c=.o)

RM = rm -f

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
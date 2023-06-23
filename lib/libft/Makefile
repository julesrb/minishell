# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbussier <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/01 10:37:39 by gbussier          #+#    #+#              #
#    Updated: 2022/12/19 16:52:44 by gbussier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CFLAGS	:= -Wextra -Wall -Werror

HEADERS	:= -I ./include
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@echo "Processus completion: 100%"
	
%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf " Compiling: $(notdir $<)"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: clean all

compile:
	@cc -Wall -Wextra -Werror main.c -L. -lft

.PHONY: all, clean, fclean, re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubernar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/22 15:34:46 by jubernar          #+#    #+#              #
#    Updated: 2023/06/22 15:34:48 by jubernar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -----------\ Name \--------------------------------------------------------- #

NAME	= minishell

# -----------\ Directories \-------------------------------------------------- #

INC_DIREC = includes/
SRC_DIREC = sources/
OBJ_DIREC = objects/
LIBFT_DIR = lib/libft/

# -----------\ Compilation \-------------------------------------------------- #

CC		= cc 
AR		= ar -rcs
MD		= -mkdir -p
CFLAGS	= -Wall -Werror -Wextra

# -----------\ Files & sources \---------------------------------------------- #

INCS = -I $(INC_DIREC) -I $(LIBFT_DIR)includes/

LIBS = $(LIBFT_DIR)libft.a

SRC_FILES = main \
			banner
			

SRCS = $(addprefix $(SRC_DIREC), $(addsuffix .c, $(SRC_FILES)))
OBJS = $(addprefix $(OBJ_DIREC), $(addsuffix .o, $(SRC_FILES)))

# -----------\ Rules \-------------------------------------------------------- #

$(NAME) : all

libft:
				@$(MAKE) -sC $(LIBFT_DIR)

all: $(OBJ_DIREC) $(OBJS) libft
				$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(INCS) -o $(NAME)
				$(CC) -g $(CFLAGS) $(OBJS) $(LIBS) $(INCS) -o $(NAME)
				@echo "- $(NAME) created !"

$(OBJ_DIREC)%.o : $(SRC_DIREC)%.c
				@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
				@echo "- Compiled $<"

$(OBJ_DIREC):
				@$(MD) $(OBJ_DIREC)
				@echo "- Created folder $(OBJ_DIREC)"

clean :
				@$(MAKE) -sC $(LIBFT_DIR) clean
				@echo "- Deleted LIBFT successfully"
				@rm -fr $(OBJ_DIREC)
				@echo "- Deleted $(OBJ_DIREC) successfully"

fclean :		clean
				@rm -fr $(LIBFT_DIR)libft.a
				@echo "- Deleted libft.a successfully"
				@rm -fr $(NAME)
				@echo "- Deleted $(NAME) successfully"

re:				fclean all

.PHONY: all clean fclean re
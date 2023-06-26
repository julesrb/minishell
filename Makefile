# -----------\ Name \--------------------------------------------------------- #

NAME	:= minishell

# -----------\ Directories \-------------------------------------------------- #

LIBFT_DIR	:= ./lib/libft/
INC_DIREC := includes/
SRC_DIREC := sources/
OBJ_DIREC := build/

# -----------\ Compilation \-------------------------------------------------- #

CFLAGS	:= -Wextra -Wall -Werror -g
MD		:= -mkdir -p

# -----------\ Files & sources \---------------------------------------------- #

HEADERS	:= -I $(INC_DIREC) -I $(LIBFT_DIR)includes/
LIBS	:= $(LIBFT_DIR)libft.a
SRCS	:= $(shell find $(SRC_DIREC) -iname "*.c")
OBJS := $(addprefix $(OBJ_DIREC), $(notdir $(SRCS:.c=.o)))

# -----------\ Rules \-------------------------------------------------------- #


all: $(NAME)

$(NAME): $(OBJ_DIREC) libft $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -lreadline
	@echo "Minishell compilation: 100%"

libft:
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIREC)%.o: $(SRC_DIREC)%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(OBJ_DIREC):
	@$(MD) $(OBJ_DIREC)
	@echo "Creating folder $(OBJ_DIREC)"

clean:
	@rm -fr $(OBJ_DIREC)
	@$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean	
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: clean all

.PHONY: all, clean, fclean, re, libft
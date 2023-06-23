NAME	:= minishell
CFLAGS	:= -Wextra -Wall -Werror -g
LIBFT	:= ./lib/libft

HEADERS	:= -I ./includes  -I $(LIBFT)/include
LIBS	:= $(LIBFT)/libft.a
SRCS	:= $(shell find ./sources -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: lib $(NAME)

lib:
	@$(MAKE) -C $(LIBFT)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -lreadline

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@$(MAKE) clean -C $(LIBFT)

fclean: clean	
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, lib
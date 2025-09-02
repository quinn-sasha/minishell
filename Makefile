NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lreadline
SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c\
$(SRCS_DIR)/utils.c\
$(SRCS_DIR)/builtin.c
OBJS = $(SRCS:.c=.o)
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

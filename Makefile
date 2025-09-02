NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LDFLAGS = -lreadline
SRCS_DIR = srcs
SRCS = \
	$(SRCS_DIR)/main.c\
	$(SRCS_DIR)/utils.c\
	$(SRCS_DIR)/builtin.c
OBJS = $(SRCS:.c=.o)
TESTS_DIR = tests
TESTS_SRCS =\
	$(SRCS_DIR)/utils.c\
	$(SRCS_DIR)/builtin.c\
	$(TESTS_DIR)/test_main.c\
	$(TESTS_DIR)/test_utils.c
TESTS_BIN = $(TESTS_DIR)/test_main

.PHONY: all clean fclean re test

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -f $(TESTS_BIN)

re: fclean all

test: $(TESTS_BIN)
	./$(TESTS_BIN)

$(TESTS_BIN): $(TESTS_SRCS) $(TESTS_DIR)/test_minishell.h
	$(CC) $(CFLAGS) -I$(TESTS_DIR) -o $@ $(TESTS_SRCS)
	chmod +x $@

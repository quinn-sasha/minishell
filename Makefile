NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)
LDFLAGS = -lreadline
INCLUDE_DIR = include
SRCS_DIR = srcs
SRCS = \
	$(SRCS_DIR)/main.c\
	$(SRCS_DIR)/utils.c\
	$(SRCS_DIR)/utils2.c\
	$(SRCS_DIR)/env.c\
	$(SRCS_DIR)/env_utils.c\
	$(SRCS_DIR)/handle_env_list.c\
	$(SRCS_DIR)/builtin.c\
	$(SRCS_DIR)/parser_pipe.c\
	$(SRCS_DIR)/parser_separator.c\
	$(SRCS_DIR)/execute_command.c\
	$(SRCS_DIR)/just_for_debug.c
OBJS_DIR = objs
OBJS := $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
TESTS_DIR = tests
TESTS_SRCS =\
	$(SRCS_DIR)/utils.c\
	$(SRCS_DIR)/utils2.c\
	$(SRCS_DIR)/env.c\
	$(SRCS_DIR)/env_utils.c\
	$(SRCS_DIR)/handle_env_list.c\
	$(SRCS_DIR)/builtin.c\
	$(SRCS_DIR)/parser_pipe.c\
	$(SRCS_DIR)/parser_separator.c\
	$(SRCS_DIR)/execute_command.c\
	$(TESTS_DIR)/test_main.c\
	$(TESTS_DIR)/test_utils.c\
	$(TESTS_DIR)/test_builtin.c\
	$(TESTS_DIR)/test_parser_pipe.c\
	$(TESTS_DIR)/test_parser_separator.c
TESTS_BIN = $(TESTS_DIR)/test_main

.PHONY: all clean fclean re test norm

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TESTS_BIN)

re: fclean all

test: $(TESTS_BIN)
	./$(TESTS_BIN)

$(TESTS_BIN): $(TESTS_SRCS) $(TESTS_DIR)/test_minishell.h
	$(CC) $(CFLAGS) -I$(TESTS_DIR) -o $@ $(TESTS_SRCS)
	chmod +x $@

norm:
	norminette $(SRCS_DIR) $(INCLUDE_DIR)

NAME := minishell
SRC_DIR := src
INCLUDE_DIR := include
LIBFT_DIR := libft

CC := cc
CFLAGS := -Wall -Wextra -Werror -I$(INCLUDE_DIR)
RM := rm -f
RMDIR := rm -rf

SIGNAL_FILES := signal/signal_handler.c \
				signal/signal_setup.c

ENVIRON_FILES := environ/environ.c \
					environ/is_identifier.c \
					environ/item.c \
					environ/map_set.c \
					environ/map.c

TOKEN_FILES := tokenize/token.c \
				tokenize/tokenize_consume.c \
				tokenize/tokenize_utils.c \
				tokenize/tokenize.c

PARSE_FILES := parse/make_simple_command.c \
				parse/parse.c \
				parse/redirect.c

LIBRARY_FILES := library/xcalloc.c \
					library/xmalloc.c \
					library/xstrdup.c \
					library/xdup.c \
					library/xdup2.c \
					library/xpipe.c \
					library/xclose.c

EXPAND_FILES := expand/expand.c \
					expand/expand_shell_parameter.c \
					expand/expand_utils.c \
					expand/is_valid_syntax_after_expansion.c \
					expand/special_parameter.c \
					expand/split_token_words.c \
					expand/word_splitting.c \
					expand/remove_quote.c

BUILTIN_FILES := builtin/builtin_export.c \
					builtin/builtin_export_sorting.c \
					builtin/builtin_exit.c \
					builtin/builtin_unset.c \
					builtin/builtin_env.c \
					builtin/builtin_echo.c \
					builtin/builtin_cd.c \
					builtin/builtin_pwd.c \
					builtin/builtin.c

ERROR_FILES := error/parse_error.c\
				error/system_error.c

EXPAND_FILES := expand/expand.c \
                expand/expand_shell_parameter.c \
                expand/is_valid_syntax_after_expansion.c \
                expand/remove_quote.c \
                expand/special_parameter.c \
                expand/split_token_words.c \
								expand/expand_utils.c \
								expand/expand_word.c \
                expand/word_splitting.c

EXEC_FILES := exec/exec.c \
				exec/pipe.c \
				exec/path.c \
				exec/redirect.c \
				exec/heredoc.c

UTILS_FILES := utils/utils_string.c\
				utils/utils_word.c

SRCFILES := main.c \
			destructor.c \
			$(UTILS_FILES) \
			$(SIGNAL_FILES) \
			$(ENVIRON_FILES) \
			$(TOKEN_FILES) \
			$(PARSE_FILES) \
			$(LIBRARY_FILES) \
			$(ERROR_FILES) \
			$(EXPAND_FILES) \
			$(EXEC_FILES) \
			$(BUILTIN_FILES)

SRCS := $(addprefix $(SRC_DIR)/, $(SRCFILES))
OBJS := $(SRCS:%.c=%.o)

LIBFT := $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

TEST_DIR := tests
TEST_DIRS := $(shell find $(TEST_DIR) -mindepth 1 -maxdepth 1 -type d)

test:
	@echo "==== Starting all tests ===="
	@for test_dir in $(TEST_DIRS); do \
		$(MAKE) -C $$test_dir test || exit 1; \
	done; \
	echo "==== All tests passed sucessfully ===="

clean_test:
	for test_dir in $(TEST_DIRS); do \
		$(MAKE) -C $$test_dir fclean; \
	done;

.PHONY: all clean fclean re test clean_test

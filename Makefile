NAME := minishell
SRC_DIR := src
OBJ_DIR := obj
INCLUDE_DIR := include
LIBFT_DIR := libft
SRCFILES := destructor.c \
            exec.c \
						main.c \
						parse.c \

CC := cc
CFLAGS := -Wall -Wextra -Werror -I
RM := rm -f
RMDIR := rm -rf

SRCS := $(addprefix $(SRC_DIR)/, $(SRCFILES))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIBFT := $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(RMDIR) $(OBJ_DIR)

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

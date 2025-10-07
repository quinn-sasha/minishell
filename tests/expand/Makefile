NAME	=	test_expand

INCLUDE_DIR = ../../include
CC			=	cc
CFLAGS	=	-Wall -Wextra -Werror -I$(INCLUDE_DIR)
RM      = rm -f

SRCS = ../../src/library/xcalloc.c \
			 ../../src/library/xstrdup.c \
			 ../../src/error/error.c \
			 ../../src/environ/environ.c \
			 ../../src/environ/is_identifier.c \
			 ../../src/environ/item.c \
			 ../../src/environ/map_set.c \
			 ../../src/environ/map.c \
			 ../../src/expand/special_parameter.c \
			 ../../src/expand/expand_shell_parameter.c \
			 ../../src/expand/is_valid_syntax_after_expansion.c \
			 ../../src/expand/expand.c \
			 ../../src/expand/word_splitting.c \
			 ../../src/expand/split_token_words.c \
			 ../../src/tokenize/tokenize.c \
			 ../../src/tokenize/token.c \
			 ../../src/parse/make_simple_command.c \
			 ../../src/parse/parse.c \
			 ../../src/parse/redirect.c \
			 ../../src/destructor.c \
			 ../../src/utils.c \
       test_append_character.c \
			 test_split_word.c \
			 test_expand_shell_parameter.c \
			 test_expand.c

SRCFILES = $(notdir $(SRCS))
OBJS = $(SRCFILES:%.c=%.o)

LIBFT_DIR = ../../libft
LIBFT		= $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME)	: $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJS)	: $(SRCS)
	$(CC) $(CFLAGS) -c $^

clean	:
	$(RM) $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean	: clean
	$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR)

re		: fclean all

test: $(NAME)
	export HELLO="hello world" \
	&& export SPACES="      " \
	&& export THREE_WORDS="kiss me baby" \
	&& ./$(NAME)

.PHONY	: all clean fclean re test

NAME	=	test_parse

INCLUDE_DIR = ../../include
CC			=	cc
CFLAGS	=	-Wall -Wextra -Werror -I$(INCLUDE_DIR)
RM      = rm -f

	SRCS = ../../src/destructor.c \
	       ../../src/tokenize/token.c \
			   ../../src/tokenize/tokenize.c \
			 	 ../../src/parse/make_simple_command.c \
			 	 ../../src/parse/parse.c \
			 	 ../../src/parse/redirect.c \
			 	 ../../src/library/xcalloc.c \
			 	 ../../src/library/xstrdup.c \
				 ../../src/error/error.c \
			 	 test_parse.c

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
	./$(NAME)

.PHONY	: all clean fclean re test

NAME	=	test_expand

INCLUDE_DIR = ../../include
CC			=	cc
CFLAGS	=	-Wall -Wextra -Werror -I$(INCLUDE_DIR)
RM      = rm -f

SRCS = ../../src/library/xcalloc.c \
			 ../../src/error/error.c \
			 ../../src/expand/expand.c \
       test_append_character.c

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

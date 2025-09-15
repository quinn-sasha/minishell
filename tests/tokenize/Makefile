NAME		=	test_tokenize

CC			=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM      = rm -f

SRCS    = ../../src/tokenize/tokenize.c \
					../../src/tokenize/destructor.c \
					main.c

OBJS		= tokenize.o \
          main.o \
					destructor.o

LIBFT_DIR	= ../../libft
LIBFT		= $(LIBFT_DIR)/libft.a

all		: $(NAME)

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

.PHONY	: all clean fclean re

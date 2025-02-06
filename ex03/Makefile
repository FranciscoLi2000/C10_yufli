NAME = ft_hexdump
SRC = ft_hexdump.c
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC)
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)
re: fclean all
.PHONY: all clean fclean re

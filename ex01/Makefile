NAME = ft_cat
SRC = ft_cat.c
CC = cc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

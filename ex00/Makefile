NAME = ft_display_file
SRC = ft_display_file.c
CC = cc
CFLAGS = -Wall -Wextra -Werror

.PHONY: all clean fclean
all: $(NAME)
$(NAME): $(SRC)
	$(CC) $(CFLAGS) $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	@echo "Removing object files..."
	@rm -f *.o
fclean: clean
	@echo "Removing $(NAME)..."
	@rm -f $(NAME)

NAME = so_long
CFLAGS =    -g3  -Wall -Wextra -Werror
CC = cc

CFILES = main.c get_next_line.c get_next_line_utils.c utils1.c moves.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJ = $(CFILES:.c=.o)


all: $(NAME)

$(NAME) : $(OBJ) so_long.h get_next_line.h
	$(CC) $(OBJ) -lmlx -lXext -lX11 -o $(NAME)


clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all 

.PHONY: all clean fclean re

NAME = so_long
CFLAGS =    -g3  -Wall -Wextra -Werror
CC = cc #-fsanitize=address

CFILES = main.c get_next_line.c get_next_line_utils.c utils1.c utils2.c utils3.c utils4.c utils5.c utils6.c moves.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

OBJ = $(CFILES:.c=.o)


all: $(NAME)

$(NAME) : $(OBJ) so_long.h
	$(CC) $(OBJ) -lmlx -lXext -lX11 -o $(NAME)


clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean all 

.PHONY: all clean fclean re

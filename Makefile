##
## EPITECH PROJECT, 2024
## Makefile
## File description:
## ok
##


SRC = *.c
NAME = empire
CFLAGS = -g3 -I./libempire-11/include
LDFLAGS = -L./libempire-11 -lempire -lpthread
LD_LIBRARY_PATH = ./libempire-11/libempire.so

all: $(NAME)

$(NAME): $(SRC)
	gcc $(CFLAGS) -o $(NAME) $(SRC) $(LDFLAGS)

clean:
	rm -f *#

fclean: clean
	rm -f $(NAME)

re: fclean all

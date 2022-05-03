NAME = philosopher

SRC = main.c action.c controlor.c utilitaire.c utilitaire2.c

OBJ = main.o action.o controlor.o utilitaire.o utilitaire2.o

CC = gcc $(CFALGS)

CFALGS = -pthread -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJ)
	@$(CC) $(OBJ) -o$(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

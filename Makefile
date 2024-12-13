
CC = cc
CFLAGS = -Wall -Wextra -Werror  -fsanitize=thread -g3
 

NAME = philo
SRC_FILES = philo.c philo_init.c philo_utils.c \
			parsing.c parsing_utils.c\
			supervisor.c  routine.c\
			mutexes_init.c

	
OBJ_FILES = $(SRC_FILES:.c=.o)

.SECONDARY: $(OBJ_FILES)

all : $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $(NAME)

clean:
	rm -rf $(OBJ_FILES)

fclean: clean
	rm -rf $(NAME)

re: fclean all
ret: re
	rm -rf $(OBJ_FILES)
	clear
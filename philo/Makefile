NAME=philo

FLAGS=-Wall -Wextra -Werror

SRC=main.c \
	check_argument.c \
	init_inputs.c \
	start_routine.c \
	getter_setter.c \
	philo_routine.c \
	output.c \
	utils.c

OBJ=$(SRC:.c=.o)

%.o: %.c philo.h
	$(CC) $(FLAGS) -c $< -o $@

all:$(NAME)

$(NAME): $(OBJ)
	cc $(FLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
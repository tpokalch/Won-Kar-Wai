NAME = game_2048
SRC = main.c resize.c map.c tile.c finished.c state.c  \
	  state_start.c state_in_progress.c state_paused.c \
	  state_finished.c state_exit.c swipe.c movement.c \
	  swipe2.c swipe3.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Werror -Wextra
LIBS = -lncurses
CC = gcc

ifneq (${SIZE},)
	MAP_SIDE_SIZE = -DMAP_SIDE_SIZE=${SIZE}
endif

all: $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@ $(MAP_SIDE_SIZE)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

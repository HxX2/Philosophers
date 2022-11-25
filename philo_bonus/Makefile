SRC = philo.c src/utils.c src/parse.c src/routine.c src/proccess.c
CC = cc
NAME = philo_bonus
FLAGS = -Wextra -Werror -Wall
HEADER = "\033[0;35m   █▀▀█ █░░█ ░▀░ █░░ █▀▀█ █▀▀ █▀▀█ █▀▀█ █░░█ █▀▀ █▀▀█ █▀▀  \n   █▄▄█ █▀▀█ ▀█▀ █░░ █░░█ ▀▀█ █░░█ █░░█ █▀▀█ █▀▀ █▄▄▀ ▀▀█   \n   █░░░ ▀░░▀ ▀▀▀ ▀▀▀ ▀▀▀▀ ▀▀▀ ▀▀▀▀ █▀▀▀ ▀░░▀ ▀▀▀ ▀░▀▀ ▀▀▀\033[0;0m"
FOOTER = "\033[0;35m➔\033[0;0m type \033[0;34m./$(NAME)\033[0;0m to run the programme."

all: $(NAME) | footer

header :
	@echo
	@echo $(HEADER)
	@echo

footer :
	@echo $(FOOTER)

$(NAME): ${SRC} | header
	@echo "\033[0;35m\033[1m────── making philosophers ──────\033[0;0m"
	@printf "\033[2m"
	$(CC) $(FLAGS) -o $(NAME) $(SRC) 
	@echo "\033[0;0m"

clean: | header
	@echo "\033[0;35m\033[1m────── clean ──────\033[0;0m"
	@printf "\033[2m"
	@echo "clean"
	@echo "\033[0;0m"
 
fclean: clean | header
	@echo "\033[0;35m\033[1m────── fclean philosophers ──────\033[0;0m"
	@printf "\033[2m"
	rm -rf $(NAME)
	rm -rf $(BNAME)
	@echo "\033[0;0m"

re: fclean all

.PHONY: all clean fclean re header footer
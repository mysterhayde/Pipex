NAME	= pipex
CC		= gcc
CFLAGS	= #-Wall -Werror -Wextra

SRC_DIR	= Sources/
SRC		= main.c \
		  pipex.c \
		  binary.c \
		  free_struct.c

SOURCES	= $(addprefix $(SRC_DIR),$(SRC))

OBJ_DIR	= Objects/
OBJ		= $(SRC:.c=.o)
OBJECTS	= $(addprefix $(OBJ_DIR),$(OBJ))

LIBFT	= libft/libft.a

GREEN = \033[1;32m
RESET = \033[0m

all: $(OBJ_DIR) $(NAME)

$(LIBFT):
	$(MAKE) -C libft

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(NAME): $(LIBFT) $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -Llibft -lft -o $(NAME)
	echo "$(GREEN)$(NAME) compiled$(RESET)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a

re: fclean all
.SILENT:
.PHONY: all clean fclean re
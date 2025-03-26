NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = cub3d.c check_element.c \
	utils.c init_struct.c \
	getnextline/get_next_line.c \
	getnextline/get_next_line_utils.c

TRASH_DIR = trash
OBJS = $(SRCS:%.c=$(TRASH_DIR)/%.o)

RM = rm -rf

all: $(NAME)

$(TRASH_DIR):
	mkdir -p $(TRASH_DIR) $(dir $(OBJS)) # Crée tous les sous-dossiers nécessaires

$(NAME): $(TRASH_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(TRASH_DIR)/%.o: %.c cub3d.h err_mess.h | $(TRASH_DIR)
	mkdir -p $(dir $@) # Assure que le dossier de destination existe
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TRASH_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

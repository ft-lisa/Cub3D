NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Trouver tous les fichiers source (.c) dans tous les dossiers
SRC_DIRS = . checker getnextline
SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

# Transformer les .c en .o dans trash/
TRASH_DIR = trash
OBJS = $(SRCS:%.c=$(TRASH_DIR)/%.o)

RM = rm -rf

all: $(NAME)

# Créer le dossier trash et tous les sous-dossiers nécessaires
$(TRASH_DIR):
	mkdir -p $(TRASH_DIR) $(sort $(dir $(OBJS)))

$(NAME): $(TRASH_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilation en gardant la structure des sous-dossiers dans trash/
$(TRASH_DIR)/%.o: %.c | $(TRASH_DIR)
	mkdir -p $(dir $@)  # Assure que le sous-dossier existe
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(TRASH_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

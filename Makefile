# NAME = cub3d

# CC = cc
# CFLAGS = -Wall -Wextra -Werror -g

# # Trouver tous les fichiers source (.c) dans tous les dossiers
# SRC_DIRS = . checker getnextline
# SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

# # Transformer les .c en .o dans trash/
# TRASH_DIR = trash
# OBJS = $(SRCS:%.c=$(TRASH_DIR)/%.o)

# RM = rm -rf

# all: $(NAME)

# # Créer le dossier trash et tous les sous-dossiers nécessaires
# $(TRASH_DIR):
# 	mkdir -p $(TRASH_DIR) $(sort $(dir $(OBJS)))

# $(NAME): $(TRASH_DIR) $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# # Compilation en gardant la structure des sous-dossiers dans trash/
# $(TRASH_DIR)/%.o: %.c | $(TRASH_DIR)
# 	mkdir -p $(dir $@)  # Assure que le sous-dossier existe
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) $(TRASH_DIR)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

CC = cc -g
CFLAGS = -Wall -Werror -Wextra
MLX_PATH = minilibx-linux

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include

SRC_FILES = $(wildcard *.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

MLX = $(MLX_PATH)/libmlx.a

NAME = cub3d

all: $(NAME)

$(NAME): $(OBJ_FILES) $(MLX)
	@$(CC) $(CFLAGS) -o $@ $^ -L$(MLX_PATH) -lmlx -lXext -lX11 -lGL -lm
	@echo "$(NAME): $(GREEN)object files were created$(RESET)"
	@echo "$(NAME): $(GREEN)$(NAME) was created$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(MLX_PATH) -c -o $@ $<
	@echo "$(NAME): $(GREEN)$(OBJ_DIR) was created$(RESET)"

$(MLX):
	@$(MAKE) -C $(MLX_PATH)
	@echo "$(NAME): $(GREEN)$(MLX) was created$(RESET)"

clean:
	@$(MAKE) -C $(MLX_PATH) clean
	@rm -r $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"


fclean: 
	@rm $(NAME)
	@echo "$(NAME): $(RED)$(NAME) was deleted$(RESET)"
	@$(MAKE) -C $(MLX_PATH) clean
	@rm -r $(OBJ_DIR)
	@echo "$(NAME): $(RED)$(OBJ_DIR) was deleted$(RESET)"
	@echo "$(NAME): $(RED)object files were deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re

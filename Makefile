# Nom du programme
NAME = cub3d

# Répertoires
SRC_DIRS = . ./checker ./getnextline
OBJ_DIR = trash
MLX_DIR = ./minilibx-linux

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR)
LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# Fichiers sources et objets
SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# Cible principale
all: $(MLX_DIR)/libmlx.a $(NAME)

# Compilation du programme
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Compilation des .o dans trash
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation de la minilibx
$(MLX_DIR)/libmlx.a:
	$(MAKE) -C $(MLX_DIR)

# Nettoyage
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(MLX_DIR) clean

fclean: clean
	rm


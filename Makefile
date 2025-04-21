# # Nom du programme
# NAME = cub3d

# # Répertoires
# SRC_DIRS = . ./checker ./getnextline
# OBJ_DIR = trash
# MLX_DIR = ./minilibx-linux

# # Compiler
# CC = cc
# CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR)
# LDFLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

# # Fichiers sources et objets
# SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
# OBJS = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# # Cible principale
# all: $(MLX_DIR)/libmlx.a $(NAME)

# # Compilation du programme
# $(NAME): $(OBJS)
# 	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# # Compilation des .o dans trash
# $(OBJ_DIR)/%.o: %.c
# 	@mkdir -p $(dir $@)
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Compilation de la minilibx
# $(MLX_DIR)/libmlx.a:
# 	$(MAKE) -C $(MLX_DIR)

# # Nettoyage
# clean:
# 	rm -rf $(OBJ_DIR)
# 	$(MAKE) -C $(MLX_DIR) clean

# fclean: clean
# 	rm



NAME = cub3d

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

MLX_DIR = ./minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

INCLUDES = -I. -I$(MLX_DIR) -I./getnextline -I./checker

SRCS = \
	cub3d.c \
	fill_struct.c \
	fill_struct2.c \
	init_struct.c \
	utils.c \
	getnextline/get_next_line.c \
	getnextline/get_next_line_utils.c \
	ft_split.c \
	checker/check_color_texture.c \
	checker/check_element.c \
	checker/check_map.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) $(INCLUDES) -o $(NAME)

clean:
	$(MAKE) clean -C $(MLX_DIR)
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(MLX_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re


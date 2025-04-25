NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm -lz

S_DIR = srcs
O_DIR = .objs

SRCS = 	\
	checker/check_color_texture.c \
	checker/check_element.c \
	checker/check_map.c \
	getnextline/get_next_line.c \
	getnextline/get_next_line_utils.c \
	ft_split.c \
	cub3d.c \
	fill_struct.c \
	fill_struct2.c \
	init_struct.c \
	utils.c \
	movement.c \
	draw_game.c \

OBJS = $(SRCS:%.c=$(O_DIR)/%.o)

RESET = \033[0m
GREEN = \033[0;32m
RED	= \033[0;31m

COUNTER_FILE = .counter_makefile


all: reset_counter $(NAME)
	@if [ ! -f .built ]; then \
		echo "$(NAME): everything is already up to date."; \
	fi
	@rm -f .built

mlx:
	make -C ./minilibx-linux

bonus: all

$(O_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I./hdrs/ -c $< -o $@
	@count=`cat $(COUNTER_FILE)`; \
	count=`expr $$count + 1`; \
	echo $$count > $(COUNTER_FILE); \
	echo -n "\rCub3D: compiling... $$count/$(words $(SRCS))"

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -I./hdrs/ $(OBJS) $(LIBS) -o $(NAME)
	@echo "\n$(NAME): $(GREEN)$(NAME)$(RESET) has been compiled."
	@rm $(COUNTER_FILE)
	@touch .built

clean:
	@rm -rf $(O_DIR) $(COUNTER_FILE) .built
	@echo "$(NAME): ${RED}${O_DIR}${RESET} has been deleted."

fclean:
	@rm -rf $(O_DIR) $(NAME) $(COUNTER_FILE) .built
	@echo "$(NAME): ${RED}${O_DIR}${RESET} and ${RED}${NAME}${RESET} have been deleted."

re: fclean all

reset_counter:
	@echo 0 > $(COUNTER_FILE)

.PHONY: all bonus clean fclean re reset_counter

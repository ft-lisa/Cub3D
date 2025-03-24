NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = cub3d.c check_map.c \
       getnextline/get_next_line.c \
       getnextline/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c cub3d.h err_mess.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
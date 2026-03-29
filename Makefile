CX = cc
CXFLAGS = -Wall -Wextra -Werror -g3

MINILIBXFLAGS = -L/opt/X11/lib -lX11 -lXext -lm

SRCS =	main.c \
		map.c \
		exit.c \
		backtrack.c \
		color.c \
		utils.c \
		free.c \
		check.c \
		game.c \
		render.c \
		player.c \
		get_next_line/get_next_line_bonus.c \
		get_next_line/get_next_line_utils_bonus.c

OBJS = $(SRCS:.c=.o)
OUTPUT = cub3D

LIB_PRINTF = ft_printf/libftprintf.a
LIB_MINILIBX = minilibx-linux/libmlx.a
LIB_FT = libft/libft.a
LIBS = $(LIB_PRINTF) $(LIB_MINILIBX) $(LIB_FT)

all: $(OUTPUT)

$(LIB_PRINTF):
	make -C ft_printf

$(LIB_MINILIBX):
	make -C minilibx-linux

$(LIB_FT):
	make -C libft

$(OUTPUT): $(OBJS) $(LIBS)
	$(CX) $(CXFLAGS) $(OBJS) -o $(OUTPUT) -I includes $(LIBS) $(MINILIBXFLAGS)

%.o: %.c
	$(CX) $(CXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C ft_printf
	make clean -C minilibx-linux
	make clean -C libft

fclean: clean
	rm -f $(OUTPUT)
	rm -f $(LIB_PRINTF)
	rm -f $(LIB_MINILIBX)
	rm -f $(LIB_FT)

re: fclean all

.PHONY: all clean fclean re

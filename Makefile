# all, clean, fclean, re, bonus
# Program name => cub3D

# Flags ==========================================================
# The flag (-O3 -ffast-math) is used for optimization.
# The flag (-framework) is used to specify the required frameworks.
# the flag (-lglfw) is for linking the glfw library
# the flag (-L) is for the path to the glfw library
# the flag (-o) is for the name of the executable file
# ================================================================

# Example : (mac - linux)
# cc -O3 -ffast-math -framework Cocoa -framework OpenGL -framework IOKit -lglfw (path to libmlx42.a) -L(path to glfw library) cub3d.c -o cub

NAME = cub3d

# Mlx - includes
MLX_DIR = ./lib/mlx
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_INCLUDE = -I$(MLX_DIR)

CFLAGS = -ffast-math -I/usr/include/X11 #-g -O3 
LDFLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/x86_64-linux-gnu -lX11 -lXext -lm	

# SRCS ============>
LIBFT_SRCS = $(addprefix ./lib/libft/, ft_strlen.c ft_strncmp.c ft_strrchr.c \
	ft_strlcpy.c ft_substr.c ft_split.c ft_strjoin.c ft_memcpy.c ft_strdup.c ft_gnl.c \
	ft_atoi.c ft_strtrim.c ft_memset.c ft_bzero.c ft_calloc.c )
SRCS = $(LIBFT_SRCS) $(addprefix ./src/, cub3d.c parser.c cleanup.c utils.c raycasting.c init.c window.c player.c init_player.c renderer.c utils_raycasting.c)
# ==================

# OBJS ============>
OBJS = $(SRCS:.c=.o)
# ==================

all : $(NAME)

.c.o :
	cc $(CFLAGS) $(MLX_INCLUDE) -c $< -o $@
$(NAME) : $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

# cleaning
clean : 
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re : fclean all

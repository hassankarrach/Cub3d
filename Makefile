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

MLX_DIR = minilibx-linux
MLX = libmlx.a

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

# SRCS ============>
LIBFT_SRCS = $(addprefix ./lib/libft/, ft_strlen.c ft_strncmp.c ft_strrchr.c \
	ft_strlcpy.c ft_substr.c ft_split.c ft_strjoin.c ft_memcpy.c ft_strdup.c ft_gnl.c \
	ft_atoi.c ft_strtrim.c ft_memset.c ft_bzero.c ft_calloc.c )
SRCS = $(LIBFT_SRCS) $(addprefix ./src/, cub3d.c parser.c cleanup.c utils.c)
# ==================

# OBJS ============>
OBJS = $(SRCS:.c=.o)
# ==================

all : $(NAME)

.c.o :
	cc -g $(CFLAGS) -c $< -o $@
$(NAME) : $(OBJS)
	cc -g $(CFLAGS) $(CFLAGS) $(OBJS) -o $(NAME) 
	

# cleaning
clean : 
	rm -rf $(OBJS)
fclean : clean
	rm -rf $(NAME)
re : fclean all

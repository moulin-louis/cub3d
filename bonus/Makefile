# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 13:30:11 by loumouli          #+#    #+#              #
#    Updated: 2023/02/14 12:22:30 by loumouli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ################################## #
#               COMMAND              #
# ################################## #
CC			= cc
MKDIR		= mkdir -p
RM			= rm -rf

# ################################## #
#              EXEC NAME             #
# ################################## #
NAME		= cub3D_bonus

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= src
C_FILES		=	main_bonus.c						\
				error_exit_bonus.c					\
				rendering/rendering_bonus.c			\
				rendering/camera_bonus.c			\
				rendering/calcul_bonus.c			\
				rendering/color_bonus.c				\
				rendering/minimap_bonus.c			\
				rendering/textures_bonus.c			\
				parsing/check_map_bonus.c			\
				parsing/check_textures_bonus.c		\
				parsing/parsing_bonus.c				\
				parsing/parsing_utils_bonus.c		\
				parsing/parsing_utils_2_bonus.c		\
				parsing/set_map_bonus.c				\
				parsing/set_textures_bonus.c		\


SRCS		= $(patsubst %, $(C_DIR)/%, $(C_FILES))

# ################################## #
#               OBJECTS              #
# ################################## #
O_DIR		= objs
O_FILES		= $(C_FILES:.c=.o)
OBJS		= $(patsubst %, $(O_DIR)/%, $(O_FILES))

# ################################## #
#                FLAGS               #
# ################################## #
CFLAGS		= -Wall -Wextra -Werror -g -MMD

# ################################## #
#                INCLUDES            #
# ################################## #
CINCLUDES	=	-I ./inc -I ./lib/libft/inc -I ./lib/minilibx-linux
MLX			= 	./lib/minilibx-linux/libmlx.a
LIBFT 		= 	./lib/libft/libft.a

# ################################## #
#                RULES               #
# ################################## #

all:	$(NAME)

$(O_DIR):
			$(MKDIR) $(O_DIR)
			$(MKDIR) $(O_DIR)/parsing
			$(MKDIR) $(O_DIR)/rendering

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC)  $(CFLAGS) $(CINCLUDES) -c $< -o $@


$(MLX):
		@echo "Compiling MLX from source :"
		make -C ./lib/minilibx-linux

$(LIBFT):
		make -C ./lib/libft


$(NAME): $(MLX) $(LIBFT) $(O_DIR) $(OBJS)
			$(CC)  $(OBJS) $(CFLAGS) $(MLX) $(LIBFT) -lX11 -lXext -lm -o $@

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			make -C ./lib/libft clean
			$(RM) $(O_DIR)

fclean:
			$(RM) $(O_DIR)
			make -C ./lib/minilibx-linux clean
			make -C ./lib/libft fclean
			$(RM) $(NAME)

re:			fclean all

.PHONY: all clean fclean re

-include ./objs/*.d
-include ./objs/rendering/*.d
-include ./objs/parsing/*.d

.NOTPARALLEL:fclean
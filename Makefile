# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 13:30:11 by loumouli          #+#    #+#              #
#    Updated: 2023/02/16 12:54:18 by loumouli         ###   ########.fr        #
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
NAME		= cub3D

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= src
C_FILES		=	main.c						\
				error_exit.c				\
				rendering/rendering.c		\
				rendering/camera.c			\
				rendering/calcul.c			\
				rendering/color.c			\
				rendering/textures.c		\
				parsing/parsing.c			\
				parsing/check_map.c			\
				parsing/set_map.c			\
				parsing/parsing_utils.c		\
				parsing/set_textures.c		\
				parsing/set_textures_2.c		\
				parsing/check_textures.c	\
				parsing/parsing_utils_2.c	
				
					
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
			$(RM) ${NAME}
			make -C ./lib/libft clean
			$(RM) $(O_DIR)

fclean:	
			$(RM) ${NAME}
			$(RM) $(O_DIR)
			make -C ./lib/minilibx-linux clean
			make -C ./lib/libft fclean
			$(RM) $(NAME)

re:			fclean all

bonus:
			make -C ./bonus/ all

bonus_re:
			make -C ./bonus/ re

bonus_fclean:
			make -C ./bonus/ fclean

bonus_clean:
			make -C ./bonus/ clean


.PHONY: all clean fclean re bonus bonus_re bonus_fclean bonus_clean

-include ./objs/*.d
-include ./objs/rendering/*.d
-include ./objs/parsing/*.d

.NOTPARALLEL:fclean
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: loumouli <loumouli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/13 13:30:11 by loumouli          #+#    #+#              #
#    Updated: 2023/02/03 16:01:17 by loumouli         ###   ########.fr        #
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
NAME		= cub3d

# ################################## #
#               SOURCES              #
# ################################## #
C_DIR		= src
C_FILES		=	main.c					\
				parsing/parsing.c		\
				rendering/rendering.c	\
				rendering/get_rgba.c	\
					
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
CINCLUDES	=	-I ./inc -I ./libft/inc -I ./MLX42/include/MLX42
MLX			= 	./MLX42/build/libmlx42.a
LIBFT 		= 	./libft/libft.a

# ################################## #
#                RULES               #
# ################################## #

all:	$(NAME)

$(O_DIR):
			$(MKDIR) $(O_DIR)
			$(MKDIR) $(O_DIR)/parsing
			$(MKDIR) $(O_DIR)/rendering

$(O_DIR)/%.o: $(C_DIR)/%.c
			$(CC) $(CFLAGS) $(CINCLUDES) -c $< -o $@


$(MLX):
		@echo "Compiling MLX from source :"
		@echo
		cmake ./MLX42 -B ./MLX42/build
		cmake --build ./MLX42/build

$(LIBFT):
		make -C ./libft


$(NAME): $(MLX) $(LIBFT) $(O_DIR) $(OBJS)
			$(CC) $(OBJS) $(CFLAGS) $(MLX) $(LIBFT) -ldl -lglfw -o $@

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			make -C ./libft clean
			$(RM) $(O_DIR)

fclean:		clean
			${RM} ./MLX42/build
			make -C ./libft fclean
			$(RM) $(NAME)


re:			fclean all

.PHONY: all clean fclean re

-include ./objs/*.d

.NOTPARALLEL:fclean
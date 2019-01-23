# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/01 02:51:44 by wta               #+#    #+#              #
#    Updated: 2019/01/19 23:37:13 by awoimbee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = clang

CFLAGS		=	-Wall -Wextra -Werror -Ofast

SRC_NAME=	main.c			bresenham.c		\
			check_bounds.c	error.c			\
			init.c			utils.c			\
			keys_handlers.c	movements.c		\
			minimap.c		raycasting.c	\
			read_file.c		read_textures.c	\
			vec2_op0.c		vec2_op1.c		\
			draw_3d.c


################################################################################

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH =	srcs
OBJ_PATH =	objs

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

LDLIBS = -lft -lmlx -lm -lpthread

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	LIBX_FD = ./minilibx_macos
	LDLIBS += -framework OpenGL -framework AppKit
else
	LIBX_FD = ./minilibx_x11
	LDLIBS += -lXext -lX11
	#Don't forget you need libxext-dev & libx11-dev
endif

LDFLAGS = -Llibft -L$(LIBX_FD)
LIBS = libft/libft.a $(LIBX_FD)/libmlx.a

CFLAGS += -I./includes -I$(LIBX_FD) -I./libft

################################################################################

all : $(NAME)

libft/libft.a :
	@printf "$(YLW)Making libft...$(EOC)\n"
	@make -s -j -C libft/

$(LIBX_FD)/libmlx.a :
	@printf "$(YLW)Making libx...$(EOC)\n"
	@make -s -j all -C $(LIBX_FD)

$(NAME) : $(LIBS) $(OBJ)
	@printf "$(GRN)Linking $(NAME)...$(EOC)\n"
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJ_PATH) :
	@mkdir -p $(OBJ_PATH) 2> /dev/null
	@printf "$(GRN)Building with \"$(CFLAGS)\":$(EOC)\n"

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c | $(OBJ_PATH)
	@printf "\t$(CC) (...) $@\n"
	@$(CC) $(CFLAGS) -o $@ -c $<

libclean :
	@printf "$(RED)Cleaning libx...$(EOC)\n"
	@make -s clean -C $(LIBX_FD)
	@printf "$(RED)Cleaning libft...$(EOC)\n"
	@make -s fclean -C libft

objclean :
	@printf "$(RED)Cleaning objects...$(EOC)\n\trm -rf $(OBJ_PATH)\n"
	@rm -rf $(OBJ_PATH)

outclean :
	@printf "$(RED)Cleaning $(NAME)...$(EOC)\n\trm -f $(NAME)\n"
	@rm -f $(NAME)

clean	:	libclean	objclean
fclean	:	clean		outclean
re		:	fclean		all
sfclean	:	objclean	outclean
sre		:	sfclean		$(NAME)

.PHONY: all libclean objclean clean re fclean sfclean sre

RED = \033[1;31m
GRN = \033[1;32m
YLW = \033[1;33m
EOC = \033[0m

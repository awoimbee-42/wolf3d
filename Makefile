# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/01 02:51:44 by wta               #+#    #+#              #
#    Updated: 2019/01/16 06:28:31 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_GREEN		=	\033[0;32m
_WHITE		=	\033[m
_YELLOW		=	\033[0;33m
_DYELLOW	=	\x1b[33;01m
# VARIABLES #
NAME		=	wolf3d
SRCSDIR		=	srcs
LIBFTPATH	=	libft
LIBFTLIB	=	libft.a
LIBFT		=	$(addprefix $(LIBFTPATH)/,$(LIBFTLIB))
INCDIR		=	includes
MLXDIR		= 	minilibx_macos
OBJDIR		=	objs
OBJ			=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
CC			=	gcc
INC			=	-I $(INCDIR) -I $(MLXDIR)
CFLAGS		=	-Wall -Wextra -Werror
MLXLIB		=	-L $(MLXDIR) -lmlx
MLXFLAG		=	-framework OpenGL -framework Appkit
SRCS=			\
check_bounds.c	\
error.c			\
main.c			\
read_file.c		\
utils.c			\
vec2_op0.c		\
raycasting.c	\
read_textures.c
HEADER		=	\
wolf3d.h
# RULES #
all : $(NAME)
# NAME #
$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(MLXLIB) $(MLXFLAG) $(INC) $(OBJ) $(LIBFT) -o $@
	@echo "\n$(_GREEN)[CREATED]$(_WHITE)" $@
	@echo "All objects files are in $(_DYELLOW)obj$(_WHITE)/"
# MKDIROBJ #
$(OBJDIR) :
	@mkdir $@
	@echo "\n$(_YELLOW)[CREATED]$(_WHITE)" $@
# Wolf3D #
$(addprefix $(OBJDIR)/,%.o) : $(addprefix $(SRCSDIR)/,%.c) $(addprefix $(INCDIR)/,$(HEADER)) | $(OBJDIR)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "\r                                                              \r\c"
	@echo "$(_GREEN)[OK]$(_WHITE) $@\c"
# LIBFT #
$(LIBFT) :
	@make -C $(LIBFTPATH)
	@echo "\r                                                              \r\c"
	@echo "$(_GREEN)[OK]$(_WHITE) $@\c"
# CLEAN #
clean :
	@make -C $(LIBFTPATH) clean
	@echo "$(_DYELLOW)[CLEAN]$(_WHITE)" LIBFT
	@rm -f $(OBJ)
	@echo "$(_DYELLOW)[DELETED]$(_WHITE)" OBJECTS
	@rm -rf $(OBJDIR)
	@echo "$(_DYELLOW)[DELETED]$(_WHITE)" $(OBJDIR)/
# FCLEAN #
fclean : clean
	@make -C $(LIBFTPATH) fclean
	@echo "$(_DYELLOW)[FCLEAN]$(_WHITE)" LIBFT
	@rm -f	$(NAME)
	@echo "$(_DYELLOW)[DELETED]$(_WHITE)" $(NAME)
# RE #
re : fclean all
#==============================================================================#

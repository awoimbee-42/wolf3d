# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wta <wta@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/07/28 20:09:26 by wta               #+#    #+#              #
#    Updated: 2018/12/02 16:58:03 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#=======================================================================  COLOR#
_GREEN		=	\033[0;32m
_WHITE		=	\033[m
_YELLOW		=	\033[0;33m
_DYELLOW	=	\x1b[33;01m
#==================================================================== VARIABLES#
NAME		=	libft.a
SRCSDIR		=	srcs
LIBFT		=	$(addprefix $(SRCSDIR)/,libft)
FT_PRINTF	=	$(addprefix $(SRCSDIR)/,ft_printf)
LIBFT_H		=	libft.h
FT_PRINTF_H	=	ft_printf.h
INCDIR		=	includes
OBJDIR		=	objs
OBJLIBFT	=	$(addprefix $(OBJDIR)/,$(SRCSLIBFT:.c=.o))
OBJPRINTF	=	$(addprefix $(OBJDIR)/,$(SRCSPRINTF:.c=.o))
CC			=	gcc 
INC			=	-I $(INCDIR)
CFLAGS		=	-Wall -Wextra -Werror
SRCSLIBFT		=															\
ft_atoi.c		ft_bzero.c		ft_intlen_base.c	ft_isalnum.c			\
ft_isalpha.c	ft_isascii.c	ft_isdigit.c		ft_isprint.c			\
ft_itoa.c		ft_lstadd.c		ft_lstappend.c		ft_lstdel.c				\
ft_lstdelone.c	ft_lstiter.c	ft_lstmap.c			ft_lstnew.c				\
ft_memalloc.c	ft_memccpy.c	ft_memchr.c			ft_memcmp.c				\
ft_memcpy.c		ft_memdel.c		ft_memmove.c		ft_memset.c				\
ft_putchar.c	ft_putchar_fd.c	ft_putendl.c		ft_putendl_fd.c			\
ft_putnbr.c		ft_putnbr_fd.c	ft_putstr.c			ft_putstr_fd.c			\
ft_strcat.c		ft_strchr.c		ft_strclr.c			ft_strcmp.c				\
ft_strcpy.c		ft_strdel.c		ft_strdup.c			ft_strdupdel.c			\
ft_strequ.c		ft_striter.c	ft_striteri.c		ft_strjoin.c			\
ft_strjoindel.c	ft_strlcat.c	ft_strlen.c			ft_strmap.c				\
ft_strmapi.c	ft_strncat.c	ft_strncmp.c		ft_strncpy.c			\
ft_strnequ.c	ft_strnew.c		ft_strnstr.c		ft_strrchr.c			\
ft_strsplit.c	ft_strstr.c		ft_strsub.c			ft_strtrim.c			\
ft_tolower.c	ft_toupper.c	ft_wdcpy.c			ft_word_count.c			\
ft_word_len.c	get_next_line.c ft_strjoinfree.c	ft_strndup.c			\
ft_strndupfree.c
SRCSPRINTF	=																\
ft_convert.c	ft_convert_c.c	ft_convert_d.c		ft_convert_f.c			\
ft_convert_hex.c				ft_convert_o.c		ft_convert_p.c			\
ft_convert_per.c				ft_convert_s.c		ft_convert_u.c			\
ft_lst_pf.c		ft_parse_pf.c	ft_printf.c			ft_utils.c				\
ft_utils2.c
#======================================================================# RULES #
all : $(NAME)
#=======================================================================# NAME #
$(NAME) : $(OBJLIBFT) $(OBJPRINTF) $(addprefix $(INCDIR)/,$(HEADER))
	@ar -rcs $(NAME) $(OBJLIBFT) $(OBJPRINTF)
	@echo "\n$(_GREEN)[CREATED]$(_WHITE)" $@
	@echo "All objects files are in $(_DYELLOW)obj$(_WHITE)/"
#===================================================================# MKDIROBJ #
$(OBJDIR) :
	@mkdir $@
	@echo "$(_YELLOW)[CREATED]$(_WHITE)" $@
#==================================================================# FT_PRINTF #
$(addprefix $(OBJDIR)/,%.o) : $(addprefix $(FT_PRINTF)/,%.c) | $(OBJDIR) 
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< 
	@echo "\r                                                              \r\c"
	@echo "$(_GREEN)[OK]$(_WHITE) $@\c"
#======================================================================# LIBFT #
$(addprefix $(OBJDIR)/,%.o) : $(addprefix $(LIBFT)/,%.c) | $(OBJDIR) 
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< 
	@echo "\r                                                              \r\c"
	@echo "$(_GREEN)[OK]$(_WHITE) $@\c"
#======================================================================# CLEAN #
clean :
	@rm -f $(OBJ)
	@echo "$(_DYELLOW)[DELETED]$(_WHITE)" OBJECTS
	@rm -rf $(OBJDIR)
	@echo "$(_DYELLOW)[DELETED]$(_WHITE)" $(OBJDIR)/
#=====================================================================# FCLEAN #
fclean : clean
	@rm -f	$(NAME)
	@echo "$(_DYELLOW)[DELETED]$(_WHITE)" $(NAME)
#=========================================================================# RE #
re : fclean all
#==============================================================================#

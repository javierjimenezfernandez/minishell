# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: javjimen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/31 20:31:03 by javjimen          #+#    #+#              #
#    Updated: 2025/07/20 17:33:03 by javjimen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Project name
NAME		= minishell


# Operating system name
UNAME		= $(shell uname)


# Dependancies
INCLUDES	= -Iinc -Ilibft/inc -lreadline
ifeq (UNAME, Linux)
	INCLUDES +=
else
	INCLUDES +=
endif

LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a


# List of source files
SRC_DIR		= src/
SRC			= $(addprefix $(SRC_DIR), minishell.c)


# List of object files
OBJ_DIR		= obj/
OBJ			= $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)


# List of header files
INC_DIR		= inc/
INC			= $(addprefix inc/, minishell.h)


# Compilation flags
CC			= cc
RM			= rm -rf
AR			= ar
DIR_DUP		= mkdir -p $(@D)

CFLAGS 		+= -Wall -Wextra -Werror
ARFLAGS		= -r -c -s

ifeq (UNAME, Linux)
	EXTRA_FLAGS =
else
	EXTRA_FLAGS =
endif

SANITIZE	= $(CFLAGS) -fsanitize=address


# Rule name protection
.PHONY:		all libft clean fclean re sanitize

all: 		$(NAME)


# Make rules
$(NAME):	$(LIBFT) $(OBJ) $(INC)
			$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) $(EXTRA_FLAGS) -o $(NAME)

$(LIBFT):
			make -C $(LIBFT_DIR) all

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
			$(DIR_DUP)
			$(CC) $(CFLAGS) -c $< $(INCLUDES) -o $@

clean:
			make -C $(LIBFT_DIR) clean
			$(RM) $(OBJ_DIR)

fclean:		clean
			make -C $(LIBFT_DIR) fclean
			$(RM) $(NAME)

re:			fclean all

sanitize:	$(LIBFT) $(OBJ) $(INC)
			$(CC) $(SANITIZE) $(OBJ) -o $(NAME) $(LIBFT) $(EXTRA_FLAGS)

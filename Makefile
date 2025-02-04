# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 10:33:32 by mmiguelo          #+#    #+#              #
#    Updated: 2025/02/03 11:06:51 by mmiguelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

#==============================================================================#
#                                    NAMES                                     #
#==============================================================================#

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
INC = -I./includes
LIBFT = ./my_libft/libft.a
RM = rm -rf

GENERAL = main kill
PARSING =

NAME = pipex

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

VPATH += src/parsing

#==============================================================================#
#                                    FILES                                     #
#==============================================================================#

SRC +=	$(addsuffix .c, $(GENERAL))
SRC +=	$(addsuffix .c, $(PARSING))

OBJ_DIR = obj
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: $(NAME)

$(LIBFT):
	$(MAKE) -C ./my_libft

$(OBJ_DIR):
	mkdir -p obj

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(BONUS_INC)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) clean -C ./my_libft
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C ./my_libft
	$(RM) $(NAME) $(OBJ_DIR)

re: fclean all

PHONY: all clean fclean re

.SILENT:
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmiguelo <mmiguelo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/24 10:33:32 by mmiguelo          #+#    #+#              #
#    Updated: 2025/02/11 14:33:42 by mmiguelo         ###   ########.fr        #
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

MANDATORY = pipex utils
BONUS =	pipex_bonus utils_bonus

NAME = pipex

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

SRC_PATH 	= mandatory
BONUS_PATH 	= bonus

#==============================================================================#
#                                    FILES                                     #
#==============================================================================#

SRC 		=	$(addprefix $(SRC_PATH)/, $(addsuffix .c, $(MANDATORY)))
SRC_BONUS 	=	$(addprefix $(BONUS_PATH)/, $(addsuffix .c, $(BONUS)))

OBJ_DIR = obj
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)
OBJS_BONUS = $(SRC_BONUS:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

# Rule to compile all
all: $(NAME)

# Rule to compile the libft
$(LIBFT):
	$(MAKE) -C ./my_libft

# Rule to create the object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to compile mandotory files
$(OBJ_DIR)/%.o: $(SRC_PATH)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Rule to compile bonus files
$(OBJ_DIR)/%.o: $(BONUS_PATH)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

# Rule to compile the executable
$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# Rule to compile the bonus executable
bonus: fclean $(OBJ_DIR) $(OBJS_BONUS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_BONUS) $(LIBFT) -o $(NAME)

# Rule to clean the object files
clean:
	$(MAKE) clean -C ./my_libft
	$(RM) $(OBJS) $(OBJS_BONUS)

# Rule to clean the object files and the executable
fclean: clean
	$(MAKE) fclean -C ./my_libft
	$(RM) $(NAME) $(OBJ_DIR)

# Rule to recompile the executable
re: fclean all

# Phony rules
PHONY: all clean fclean re bonus

# Silent mode
.SILENT:
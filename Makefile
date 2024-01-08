# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maraasve <maraasve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/04 15:14:38 by marieke           #+#    #+#              #
#    Updated: 2024/01/08 17:23:14 by maraasve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = gcc
CFLAGS = -Wall -Werror -Wextra
AR = ar -rcs
LIBFT_DIR = ./libft
LIBFT_NAME = $(LIBFT_DIR)/libft.a
RM = rm -rf

SRC = pipex.c utils.c childs.c
SRC_BONUS = pipex_bonus.c utils_bonus.c
BONUS_DIR = ./pipex_bonus
BONUS_NAME = $(BONUS_DIR)/pipex
OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
OBJ_BONUS = $(addprefix $(OBJ_BONUS_DIR)/,$(SRC_BONUS:.c=.o))

all: $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)

bonus: $(LIBFT_NAME) $(OBJ_BONUS)
	@if [ ! -e $(BONUS_NAME) ] || [ "$(OBJ_BONUS)" -nt $(BONUS_NAME) ]; then \
		$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJ_BONUS) -L$(LIBFT_DIR) -lft; \
	fi

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(BONUS_DIR)/%.c | $(OBJ_BONUS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)

clean:
	@make -C $(LIBFT_DIR) clean
	@$(RM) $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re

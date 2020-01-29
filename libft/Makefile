# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 18:24:03 by cchadwic          #+#    #+#              #
#    Updated: 2019/09/19 18:42:03 by cchadwic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

COMP = gcc -Wall -Werror -Wextra -I includes -c -o

OBJ_DIR = ./obj/
SRC_DIR = ./srcs/

CFIND = $(shell find $(SRC_DIR) -maxdepth 1 -type f | grep -E "\.c$$")
CFILE = $(notdir $(CFIND))
OFILE = $(CFILE:%.c=%.o)

OBJ = $(addprefix $(OBJ_DIR), $(OFILE))

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ)
	ar rc $(NAME) $(addprefix $(OBJ_DIR), $(OFILE))
	ranlib $(NAME)

$(OBJ): $(CFIND)
	$(MAKE) $(OFILE)

$(OFILE):
	$(COMP) $(OBJ_DIR)$@ $(SRC_DIR)$(@:%.o=%.c)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean flcean re

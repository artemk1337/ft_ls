# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchadwic <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/28 21:47:34 by cchadwic          #+#    #+#              #
#    Updated: 2020/02/05 16:19:21 by cchadwic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

### PATH ###
SRCS_PATH = src/
OBJ_PATH  = obj/
LIBFT_PATH = libft/

FLAGS = -Wall -Werror -Wextra
INC = -I ./inc/ -I ./$(LIBFT_PATH)includes/

SRCS_NAME = ft_main.c\
			ft_sort.c\
			ft_reverse.c\
			ft_check_perm.c\
			ft_init.c\
			ft_put.c\
			ft_error.c\
			ft_convert.c\
			get_term_size.c\
			ft_check_1.c\
			ft_get_files.c\
			ft_l.c\
			ft_other.c\
			ft_put_dop.c\

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(SRCS_NAME:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) ./inc/*
	@make -C $(LIBFT_PATH)
	@gcc $(FLAGS) $(OBJ) $(INC) -L $(LIBFT_PATH) -lft -o $(NAME)
	@echo "\033[32mBinary\t\t\\033[1;32m$(NAME)\033[1;0m\033[32m created.\033[0m"

$(OBJ_PATH)%.o: $(SRCS_PATH)%.c
	@mkdir -p obj
	@gcc -c $(FLAGS) $(INC) $< -o $@
	@echo "\033[34m\033[1mCompilation of\t\033[0m\033[36m$(notdir $<)\033[1m\033[34m done.\033[0m"

clean:
	@make -C $(LIBFT_PATH)/ clean
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\033[31mObjects files\t\033[1;31m$(OBJ)\033[1;0m\033[31m removed.\033[0m"

fclean: clean
	@make -C $(LIBFT_PATH)/ fclean
	@/bin/rm -rf $(NAME)
	@echo "\033[31mBin \033[1;31m$(NAME)\033[1;0m\033[31m removed.\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bamghoug <bamghoug@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/23 09:13:00 by bamghoug          #+#    #+#              #
#    Updated: 2021/06/07 16:30:43 by bamghoug         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC = pipex.c pipex2.c pipex3.c
BONUS = pipex_bonus.c pipex2_bonus.c pipex3_bonus.c
	  
FLAGS = gcc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(SRC)
	@make -C ./libft
	@$(CC) -o $(NAME) $(SRC) libft/libft.a

clean:
	@make clean -C ./libft

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

bonus: fclean
	@make -C ./libft
	@$(CC) -o $(NAME) $(BONUS) libft/libft.a

re: fclean all

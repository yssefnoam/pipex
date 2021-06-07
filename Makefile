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

SRC = pipex.c libft/libft.a
	  
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	@make -C ./libft
	@gcc -o $(NAME) $(FLAGS) $(SRC) libft/libft.a -ltermcap

clean:
	@make clean -C ./libft

fclean: clean
	@make fclean -C ./libft
	@rm -rf $(NAME)

re: fclean all

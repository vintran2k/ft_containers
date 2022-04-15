# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vintran <vintran@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/15 02:48:06 by vintran           #+#    #+#              #
#    Updated: 2022/04/15 03:04:38 by vintran          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_FT			=	ft_containers
NAME_STD		=	std_containers
SRCS_FT			=	main.cpp			\
					ft_vector.cpp		\
					ft_stack.cpp		\
					ft_map.cpp
SRCS_STD		=	std_main.cpp		\
					std_vector.cpp		\
					std_stack.cpp		\
					std_map.cpp
CC				=	@c++
FLAGS			=	-Wall -Wextra -Werror -std=c++98
OBJDIR_FT		=	objs_ft
OBJS_FT			=	$(addprefix $(OBJDIR_FT)/, $(SRCS_FT:.cpp=.o))
OBJDIR_STD		=	objs_std
OBJS_STD		=	$(addprefix $(OBJDIR_STD)/, $(SRCS_STD:.cpp=.o))

all					:	$(NAME_FT) $(NAME_STD)

$(NAME_FT)			:	$(OBJS_FT)
				$(CC) $(FLAGS) $(OBJS_FT) -o $(NAME_FT)
				@echo "\033[1;30m[$(NAME_FT)] \033[1;32mcreated !\033[0m"

$(NAME_STD)			:	$(OBJS_STD)
				$(CC) $(FLAGS) $(OBJS_STD) -o $(NAME_STD)
				@echo "\033[1;30m[$(NAME_STD)] \033[1;32mcreated !\033[0m"

${OBJDIR_FT}/%.o	:	%.cpp
				@mkdir -p $(OBJDIR_FT)
				$(CC) $(FLAGS) -c $< -o $@

${OBJDIR_STD}/%.o	:	%.cpp
				@mkdir -p $(OBJDIR_STD)
				$(CC) $(FLAGS) -c $< -o $@

clean			:
				@rm -rf $(OBJDIR_FT) $(OBJDIR_STD)
				@echo "\033[1;30m[$(OBJDIR_FT), $(OBJDIR_STD)] : \033[1;31mdeleted !\033[0m"

fclean			:	clean
				@rm -f $(NAME_FT) $(NAME_STD)
				@echo "\033[1;30m[$(NAME_FT), $(NAME_STD)] \033[1;31mdeleted !\033[0m"

re				:	fclean all

.PHONY			: 	clean fclean all re
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: asalo <asalo@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 14:37:45 by asalo             #+#    #+#              #
#    Updated: 2024/07/21 12:57:57 by asalo            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRC_DIR	= src
OBJ_DIR	= obj
SUB_DIR	= is to mem str put lst gnl printf

SRCS	= $(addprefix $(SRC_DIR)/is/, ft_isalnum.c ft_isalpha.c \
			ft_isascii.c ft_isdigit.c ft_isprint.c ft_isspace.c) \
		$(addprefix $(SRC_DIR)/lookup/, ft_lookup_space.c) \
		$(addprefix $(SRC_DIR)/to/, ft_atoi.c ft_itoa.c ft_tolower.c \
			ft_toupper.c ft_atol.c ft_atod.c) \
		$(addprefix $(SRC_DIR)/mem/, ft_bzero.c ft_calloc.c ft_memchr.c \
			ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c) \
		$(addprefix $(SRC_DIR)/put/, ft_putchar_fd.c ft_putendl_fd.c \
			ft_putnbr_fd.c ft_putstr_fd.c) \
		$(addprefix $(SRC_DIR)/str/, ft_split.c ft_strchr.c ft_strdup.c \
			ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
			ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
			ft_substr.c ft_strcmp.c ft_strinsrt.c ft_strichr.c ft_strcpy.c \
			ft_strplen.c) \
		$(addprefix $(SRC_DIR)/lst/, ft_lstadd_back.c \
			ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c \
			ft_lstiter.c ft_lstlast.c ft_lstnew.c \
			ft_lstsize.c ft_lstmap.c) \
		$(addprefix $(SRC_DIR)/gnl/, get_next_line_utils.c get_next_line.c) \
		$(addprefix $(SRC_DIR)/printf/, ft_print_format.c ft_printf.c)

OBJS_DIRS	= $(foreach dir, $(SUB_DIR), $(addprefix $(OBJ_DIR)/, $(dir)))
OBJS		= $(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INC			= -I incs/
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f

$(OBJ_DIR)/%.o :	$(SRC_DIR)/%.c
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(INC) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJS)
			@ar -rcs $(NAME) $(OBJS)

clean:
			@$(RM) $(OBJS)
			@$(RM) -r $(OBJ_DIR)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
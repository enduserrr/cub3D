NAME	=	cub3D
SRC_DIR	=	src
OBJ_DIR	=	.obj
LIBFT	=	incs/libft/libft.a
MLX		=	incs/MLX42/build/libmlx42.a

SRCS	=	$(addprefix $(SRC_DIR)/, main.c validate.c map_utils.c err.c gameplay.c test_map.c player.c draw.c raycasting.c textures.c)
OBJ		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INCS	=	-I incs -I incs/libft/incs -I incs/MLX42/include/MLX42

CC		=	cc
LIBS	=	-ldl -lglfw -pthread -lm
FLAGS	=   -Wall -Wextra -Werror
RM		=	rm -f

GREY_T	= \33[90m
GREEN_T	= \33[92m
ORANG_T	= \33[93m
RED_T	= \33[91m
BLUE_T	= \33[94m

RED_B	= \33[1;91m
GREEN_B	= \33[1;92m
ORANG_B	= \33[1;93m
GREY_B	= \33[1;90m
BLUE_B	= \33[1;94m
WHITE_B	= \33[1;97m

WHITE_F = \33[7;37m
RESET 	= \033[0m

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(dir $@)
				@$(CC) $(FLAGS) $(INCS) -c $< -o $@
				@echo "[$(GREEN_T)OK$(RESET)]$(GREY_T): $< -> $@$(RESET)"

all: build $(NAME)

$(NAME):	$(OBJ)
			@make -C incs/libft -s
			@$(MAKE) -C incs/MLX42 build
			@$(CC) $(OBJ) $(LIBFT) $(MLX) -o $(NAME) $(INCS) $(LIBS)
			@echo "$(WHITE_B)GAME BUILT SUCCESSFULLY!$(RESET)"

build:
			@cd incs/MLX42 && cmake -B build && cmake --build build -j4

clean:
			@cd incs/MLX42/build && make clean
			@$(RM) $(OBJ)
			@$(RM) -r $(OBJ_DIR)
			@make clean -C incs/libft -s
			@echo "$(ORANG_T)*.o files & obj dir removed$(RESET)"

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C incs/libft -s
			@echo "$(RED_T)all build artifacts removed$(RESET)"

re:			fclean all

.PHONY:	all clean fclean re

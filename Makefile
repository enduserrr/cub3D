NAME	=	cub3D
SRC_DIR	=	src
OBJ_DIR	=	.obj
LIBFT	=	incs/libft/libft.a
MLX		=	incs/MLX42/build/libmlx42.a

SRCS	=	$(addprefix $(SRC_DIR)/game/, gameplay.c player.c) \
			$(addprefix $(SRC_DIR)/parse/, validate.c map_info.c map_utils.c floodfill.c) \
			$(addprefix $(SRC_DIR)/render/, draw.c raycasting.c textures.c test_map.c) \
			$(addprefix $(SRC_DIR)/utils/, err.c exit_cycle.c) \
			$(addprefix $(SRC_DIR)/, main.c)

OBJ		=	$(subst $(SRC_DIR), $(OBJ_DIR), $(SRCS:.c=.o))

INCS	=	-I incs -I incs/libft/incs -I incs/MLX42/include/MLX42

CC		=	cc
LIBS	=	-ldl -lglfw -pthread -lm
FLAGS	=   -Wall -Wextra -Werror
RM		=	rm -f

GREY	= \33[90m
GREEN	= \33[92m
ORANG	= \33[93m
RED		= \33[91m
WB		= \33[1;97m
RES 	= \033[0m

$(OBJ_DIR)/%.o :	$(SRC_DIR)/%.c
					@mkdir -p $(dir $@)
					@$(CC) $(FLAGS) $(INCS) -c $< -o $@
					@echo "[$(GREEN)OK$(RES)]$(GREY): $< -> $@$(RES)"

all:		build $(NAME)

$(NAME):	$(OBJ)
			@make -C incs/libft -s
			@$(MAKE) -C incs/MLX42 build
			@$(CC) $(OBJ) $(LIBFT) $(MLX) -o $(NAME) $(INCS) $(LIBS)
			@echo "$(WB)GAME BUILT SUCCESSFULLY!$(RES)"

build:
			@cd incs/MLX42 && cmake -B build && cmake --build build -j4

clean:
			@cd incs/MLX42/build && make clean
			@$(RM) $(OBJ)
			@$(RM) -r $(OBJ_DIR)
			@make clean -C incs/libft -s
			@echo "$(ORANG)*.o files & obj dir removed$(RES)"

fclean:		clean
			@$(RM) $(NAME)
			@make fclean -C incs/libft -s
			@echo "$(RED)all build artifacts removed$(RES)"

re:			fclean all

.PHONY:	all clean fclean re

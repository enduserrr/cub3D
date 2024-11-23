NAME	=	cub3D
SRC_DIR	=	src
OBJ_DIR	=	.obj
LIBFT	=	incs/libft/libft.a
MLX		=	incs/MLX42/build/libmlx42.a

SRCS	=	$(addprefix $(SRC_DIR)/game/, clean_exit.c gameplay.c move.c) \
			$(addprefix $(SRC_DIR)/parse/, extract_map.c map_info.c map_utils.c player.c validate_map.c check_walls.c) \
			$(addprefix $(SRC_DIR)/render/, draw.c raycasting.c render_utils.c) \
			$(addprefix $(SRC_DIR)/utils/, gnl_mod.c utils.c) \
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
WB_OVER	= \33[30;47m
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
			@echo "$(GREY)* MAP FILE EXAMPLE: *" \
			"\nNO ./*/*.png\nSO ./*/*.png\nWE ./*/*.png\nEA ./*/*.png\n" \
			"\nF 11, 70, 111\nC 255, 180, 166\n\n1111\n10N1\n1111$(RES)" \
			"\n$(WB_OVER)You can play it. Enjoy!$(RES)" \
			"\n$(GREY)Execute:\t./cub3d maps/*.cub\nControls:\tWASD & ←↑→↓\nQuit:\t\tESC$(GREY)"

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

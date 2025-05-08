#include "../../incs/cub3D.h"

/**
 * @brief	Handles the screen rendering for the game.
 * @param	param	The game structure containing all the necessary information
 * 					for rendering.
 *
 * This function updates the screen by creating a new image to be displayed,
 * rendering the raycasted scene, and then displaying the image on the window.
 * If an error occurs during image creation or displaying, it calls the `out`
 * function to clean up resources and exits the program.
 */
void	screen(void *param)
{
	t_game	*game;

	game = param;
	if (game->screen)
		mlx_delete_image(game->mlx, game->screen);
	game->screen = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!game->screen)
	{
		write_err(ERROR_IMG);
		out(game);
		exit(1);
	}
	if (mlx_image_to_window(game->mlx, game->screen, 0, 0) == -1)
	{
		write_err(ERROR_WINDOW);
		out(game);
		exit(1);
	}
	raycast(game);
	game->screen->instances[0].z = 0;
}

/**
 * @brief	Handles user input for movement and rotation in the game.
 * @param	param	The game structure containing the player and movement data.
 *
 * This function checks the state of the keyboard and updates the player's
 * movement or rotation accordingly. The player can move forward, backward,
 * left, and right, and rotating the view left or right using the arrow keys.
 */
void	keys(void *param)
{
	t_game	*game;
	double	speed;
	double	bumber;

	game = param;
	speed = 3.0 * game->mlx->delta_time;
	bumber = 0.5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		move_up(game, speed, speed + bumber);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		move_down(game, speed, speed + bumber);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_right(game, speed, speed + bumber);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_left(game, speed, speed + bumber);
}

/**
 * @brief 	Loads and displays the player's weapon texture in the game.
 * @param 	game	The game structure containing the textures and weapon data.
 *
 * This function loads the weapon texture from a PNG file, creates a new
 * image for the weapon, and displays it in the game window. If any errors
 * occur during this process (e.g., texture loading or image creation), it
 * cleans up the resources and exits the program.
 */
int	get_weapon(t_game *game)
{
	game->textures->gun = mlx_load_png(GUN_PATH);
	if (!game->textures->gun)
		return (write_err(ERROR_PNG), 1);
	game->gun = mlx_new_image(game->mlx, WEAPON_W, WEAPON_H);
	if (!game->gun)
		return (write_err(ERROR_IMG), 1);
	game->gun = mlx_texture_to_image(game->mlx, game->textures->gun);
	if (!game->gun)
		return (write_err(ERROR_TXTR), 1);
	if (mlx_image_to_window(game->mlx, game->gun, WIN_WIDTH / 3, (WIN_HEIGHT
				- WEAPON_H)) == -1)
		return (write_err(ERROR_WINDOW), 1);
	game->gun->instances[0].z = 1;
	return (0);
}

/**
 * @brief 	Initializes the game, loads resources, and starts the game loop.
 * @param 	game 	The game structure containing all the necessary data for
 * 					starting the game.
 *
 * @return 	Returns 0 when the game ends successfully.
 * Initializes the game environment, including setting up the
 * window and loading the weapon texture, yhen enters the main game loop,
 * which handles rendering, input processing, and other game events.
 * The `mlx_loop_hook` is used to repeatedly call the `screen`
 * and `keys` functions during the game loop. If an error occurs during
 * initialization or the game loop, the program exits.
 */
int	gameplay(t_game *game)
{
	game->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, true);
	if (!game->mlx)
		return (write_err(ERROR_INIT), 1);
	if (get_weapon(game))
		return (1);
	mlx_loop_hook(game->mlx, screen, game);
	mlx_loop_hook(game->mlx, keys, game);
	mlx_loop(game->mlx);
	out(game);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleppala <eleppala@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:03:36 by eleppala          #+#    #+#             */
/*   Updated: 2024/10/09 12:03:38 by eleppala         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3D.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

#define PI 3.14159265

void draw_vertical(t_window *win, float x, float y, float a)
{
    int map_x;
    int map_y;
    float dx;
    float dy; 

    dx = cos(a * (PI / 180));
    dy = sin(a * (PI / 180));

    while(x > 0)
    {
        map_x = x / 100;
        map_y = y / 100;
        if (win->map[map_y][map_x] == '1')
            break;
        mlx_put_pixel(win->rays, x, y, 0xFFFFFF);
        x += dx;
        y += dy;
    }
}

void draw_horizontal(t_window *win, float x, float y, float a)
{
    int map_x;
    int map_y;
    float dx;
    float dy; 

    dx = cos(a * (PI / 180));
    dy = sin(a * (PI / 180));

    while(y > 0)
    {
        map_x = x / 100;
        map_y = y / 100;
        if (win->map[map_y][map_x] == '1')
            break;
        mlx_put_pixel(win->rays, x, y, 0xFFFFFF);
        x += dx;
        y += dy;
    }
}


void draw_rays(t_window *window)
{
    float x = window->player->ppx + 2;
    float y = window->player->ppy + 2;
    float a = window->player->pa;
    float i = 0;

    if (window->rays)
        mlx_delete_image(window->mlx, window->rays);
    if (!(window->rays = mlx_new_image(window->mlx, 1000, 1000)))
	{
		mlx_close_window(window->mlx);
		exit(1);
	}
	if (mlx_image_to_window(window->mlx, window->rays, 0, 0) == -1) 
	{
		mlx_close_window(window->mlx);
		exit(1);
	}
    while (i < 45)
    {    
        //draw_horizontal(window, x, y, a + i);
        //draw_horizontal(window, x, y, a - i);
        draw_vertical(window, x, y, a + i);
        draw_vertical(window, x, y, a - i);
        i ++;
    }
}

void draw_floor(t_window *window)
{
    draw_rays(window);
}
void draw_player(t_window *window)
{
    uint32_t x = 0;
    uint32_t y = 0;

    if (!(window->icon = mlx_new_image(window->mlx, 5, 5)))
	{
		mlx_close_window(window->mlx);
		exit(1);
	}
	if (mlx_image_to_window(window->mlx, window->icon, window->player->ppx, window->player->ppy) == -1)  // 0, 0 start position
	{
		mlx_close_window(window->mlx);
		exit(1);
	}

    while(x < 5)
    {
        while (y < 5)
        {
            mlx_put_pixel(window->icon, x, y, 0xFFFFFF);
            y ++;
         }
        y = 0;
        x ++;
    }
}

void movement(void  *param)
{
	t_window *window = param;
    float par;

    par = window->player->pa * (PI / 180);
    if (mlx_is_key_down(window->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(window->mlx);
	if (mlx_is_key_down(window->mlx, MLX_KEY_UP))
	{
        window->player->ppx += cos(par) * 5;
        window->player->ppy += sin(par) * 5;
        window->icon->instances[0].x = window->player->ppx;
        window->icon->instances[0].y = window->player->ppy;
    }
    if (mlx_is_key_down(window->mlx, MLX_KEY_DOWN))
	{
        window->player->ppx -= cos(par) * 5;
        window->player->ppy -= sin(par) * 5;
        window->icon->instances[0].x = window->player->ppx;
        window->icon->instances[0].y = window->player->ppy;
    }
    if (mlx_is_key_down(window->mlx, MLX_KEY_LEFT))
	{
        window->player->pa -= 2;
    }
    if (mlx_is_key_down(window->mlx, MLX_KEY_RIGHT))
	{
        window->player->pa += 2;
    }
    draw_floor(window);
}


/* just for now, later initialization happens after parsing */
void init_player(t_player *player)
{
    player->ppx = 500;
    player->ppy = 500;
    player->pa = 90;
}
/*
void raycasting(t_window *win)
{


}*/

void test_map(t_window *window)
{
    window->map = ft_split("1111111111-1000100001-1000000001-1000000001-1000000001-1000000001-1000000001-1000000001-1000000001-1111111111", '-'); 

    //window->map = ft_split("11111-10001-10001-10001-11111", '-');
    if (!window->map)
        exit(1);
}


int gameplay()
{
    t_window window;
    t_player player;
    int i = 0;

    window = (t_window){0};
    init_player(&player);
    test_map(&window);
    window.player = &player;
    if (!(window.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_NAME, true)))       // true: resize on
	{
		exit(0);
	}
    draw_floor(&window);
    draw_player(&window);
    //raycasting(&window); 
    mlx_loop_hook(window.mlx, movement, &window);                   //moving player
	mlx_loop(window.mlx);
	mlx_terminate(window.mlx);
    while(window.map[i] != NULL)
    {
        free(window.map[i]);
        i ++;
    }
    free(window.map);
    return (0);
}

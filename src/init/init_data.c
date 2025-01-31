/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 21:50:19 by qvan-ste          #+#    #+#             */
/*   Updated: 2025/01/31 17:14:27 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static t_player	*init_player(int player_x, int player_y)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
	{
		return (NULL);
	}
	player->pos_x = player_x;
	player->pos_y = player_y;
	return (player);
}

static t_camera	*init_camera(int view_direction_x, int view_direction_y)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	if (!camera)
	{
		return (NULL);
	}
	camera->plane_x = 0;
	camera->plane_y = 0.66;
	camera->view_dir_x = view_direction_x;
	camera->view_dir_y = view_direction_y;
	return (camera);
}

int	init_data(t_data *game, char *map_file, t_map_data *map_data)
{
    char *texture_paths[NUM_OF_TEXTURES + 1];
    int *rgb_floor;
    int *rgb_ceiling;

    game->map = create_map(map_file, map_data);
    if (!game->map)
        return (FAILURE);

    if (main_mcheck(map_data) != SUCCESS)
        return (FAILURE);
    game->player = init_player(map_data->starting[0], map_data->starting[1]);
    if (!game->player)
        return (FAILURE);
    game->camera = init_camera(map_data->cam_vieuw[0], map_data->cam_vieuw[1]);
    if (!game->camera)
        return (FAILURE);

    texture_paths[0] = map_data->no_texture;
    texture_paths[1] = map_data->so_texture;
    texture_paths[2] = map_data->we_texture;
    texture_paths[3] = map_data->ea_texture;
    texture_paths[4] = NULL;

    rgb_floor = map_data->floor_color;
    rgb_ceiling = map_data->ceiling_color;

    game->display = init_display(texture_paths, rgb_floor, rgb_ceiling);
    if (!game->display)
        return (FAILURE);

    return (SUCCESS);
}

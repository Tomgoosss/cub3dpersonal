/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:12:48 by qvan-ste          #+#    #+#             */
/*   Updated: 2025/02/05 15:43:40 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include "../libs/libft/include/libft.h"

#include <stdio.h>

void print_map_data(t_map_data *map_data)
{
    printf("Map:\n");
    if (map_data->map)
    {
        for (int i = 0; map_data->map[i]; i++)
        {
            printf("%s\n", map_data->map[i]);
        }
    }
    else
    {
        printf("Map is not initialized.\n");
    }

    printf("NO Texture: %s\n", map_data->no_texture ? map_data->no_texture : "Not initialized");
    printf("SO Texture: %s\n", map_data->so_texture ? map_data->so_texture : "Not initialized");
    printf("WE Texture: %s\n", map_data->we_texture ? map_data->we_texture : "Not initialized");
    printf("EA Texture: %s\n", map_data->ea_texture ? map_data->ea_texture : "Not initialized");

    printf("Floor Color: %d, %d, %d\n", map_data->floor_color[0], map_data->floor_color[1], map_data->floor_color[2]);
    printf("Ceiling Color: %d, %d, %d\n", map_data->ceiling_color[0], map_data->ceiling_color[1], map_data->ceiling_color[2]);
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_map_data	map_data;

	ft_bzero(&data, sizeof(t_data));
	if (validate_input(argc, argv) != SUCCESS)
	{
		printf("test1\n");
		return (FAILURE);
	}
	if (init_data(&data, argv[1], &map_data) != SUCCESS)
	{
		printf("test2\n");
		free_data(data);
		return (FAILURE);
	}
	// print_map_data(&map_data);
	execute(&data);
	free_data(data);
}

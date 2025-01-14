/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:18:48 by qvan-ste          #+#    #+#             */
/*   Updated: 2025/01/14 14:30:47 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define SUCCESS 0

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

// Structs
typedef struct s_map_data
{
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		floor_color[3];
	int		ceiling_color[3];
}	t_map_data;

// Functions
// Parsing
int		create_map(char *file, t_map_data *map_data);
int		main_mcheck(t_map_data *map_data);

//Utils
int		check_extension(char *arg);

#endif

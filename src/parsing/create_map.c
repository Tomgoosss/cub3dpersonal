/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:29:30 by qvan-ste          #+#    #+#             */
/*   Updated: 2025/01/31 15:21:09 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../../libs/libft/include/libft.h"
#include "../../include/cub3D.h"

static int	create_map_vector(t_vector_ptr *map_vector, int map_fd)
{
	char			*buf;

	buf = get_next_line(map_fd);
	if (!buf)
		return (FAILURE);
	if (ft_vecinit_ptr(map_vector, 10, sizeof(char *)) != SUCCESS)
		return (FAILURE);
	while (buf)
	{
		if (buf[ft_strlen(buf) - 1] == '\n')
			buf[ft_strlen(buf) - 1] = '\0';
		if (ft_vecappend_ptr(map_vector, buf) != SUCCESS)
		{
			free(buf);
			ft_vecdelete_ptr(map_vector);
			return (FAILURE);
		}
		buf = get_next_line(map_fd);
	}
	return (SUCCESS);
}

static char	**create_map_matrix(t_vector_ptr *map_vector)
{
	size_t	i;
	char	**map_matrix;

	i = 0;
	map_matrix = ft_calloc(map_vector -> size + 1, sizeof(char *));
	if (!map_matrix)
		return (NULL);
	while (i < map_vector -> size)
	{
		map_matrix[i] = ft_vecget_ptr(map_vector, i);
		i++;
	}
	return (map_matrix);
}

char	**create_map(char *file, t_map_data *map_data)
{
	int				map_fd;
	t_vector_ptr	map_vector;
	char			**map;
	int 			i;
	int				j;

	i = 0;
	j = 0;
	map_fd = open(file, O_RDONLY);
	if (map_fd == -1)
	{
		perror("Cub3D");
		return (NULL);
	}
	if (create_map_vector(&map_vector, map_fd) == FAILURE)
	{
		perror("Cub3D");
		close(map_fd);
		return (NULL);
	}
	map_data->map = create_map_matrix(&map_vector);
	close(map_fd);
	free(map_vector.items);
	if (!map_data->map)
		return (NULL);
	map = malloc(sizeof(char *) * (map_vector.size + 1));
	if (!map)
		return (NULL);
	while (is_not_map(map_data->map[i]))
		i++;
	while (map_data->map[i])
	{
		map[j] = map_data->map[i];
		i++;
		j++;
	}
	map[j] = NULL;
	return (map);
}

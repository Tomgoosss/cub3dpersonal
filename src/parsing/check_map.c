#include "../../libs/libft/include/libft.h"
#include "../../include/cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int init_path(char *line, char **texture)
{
	size_t len;

	if(*texture != NULL)
	{
        ft_printf_fd(2, "Error\n double path: %s\n", line);
		return(1);
	}
    while (*line && *line != ' ')
        line++;
    while (*line && *line == ' ')
        line++;
    *texture = ft_strdup(line);
    if (*texture == NULL)
        return (0);

    len = ft_strlen(*texture);
    if (len < 4 || strcmp(*texture + len - 4, ".png") != 0)
    {
        free(*texture);
        *texture = NULL;
        ft_printf_fd(2, "Error\n incorrect texture format: %s\n", line);
        return (1);
    }

    return (SUCCESS);
}
int is_not_map(char *line)
{
	static const char *list[] = {"NO ", "SO ", "WE ", "EA ", "F ", "C ", NULL};
	int i;

	i = 0;
	if (!line || line[0] == '\0' || line[0] == '\n')
		return (1);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	while(i < 6)
	{
		if(ft_strncmp(line, list[i], ft_strlen(list[i])) == 0)
			return(1);
		i++;
	}
	return (0);
}

int parse_color(char *line, int *color)
{
    int i = 0;
    int value;

    while (*line && *line != ' ')
        line++;
    while (*line && *line == ' ')
        line++;
    while (i < 3)
    {
        value = 0;
        if (!(*line >= '0' && *line <= '9'))
            return 1;
        while (*line >= '0' && *line <= '9')
        {
            value = value * 10 + (*line - '0');
            line++;
        }
        if (value < 0 || value > 255)
            return 1;
        color[i] = value;
        if (i < 2)
        {
            if (*line != ',')
                return 1;
            line++;
        }
        i++;
    }
    while (*line && *line == ' ')
        line++;
    if (*line != '\0')
        return 1;
    return SUCCESS;
}

int init_floor_ceiling(char *line, int *color)
{
    if (parse_color(line, color) != SUCCESS)
    {
        ft_printf_fd(2, "Error\nInvalid floor/ceiling color\n");
        return (1);
    }
    return (SUCCESS);
}

int init_texture(char *line, t_map_data *map_data)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        return(init_path(line, &map_data->no_texture));
    else if (ft_strncmp(line, "SO ", 3) == 0)
        return(init_path(line, &map_data->so_texture));
    else if (ft_strncmp(line, "WE ", 3) == 0)
        return(init_path(line, &map_data->we_texture));
    else if (ft_strncmp(line, "EA ", 3) == 0)
        return(init_path(line, &map_data->ea_texture));
    if (ft_strncmp(line, "F ", 2) == 0)
        return(init_floor_ceiling(line, map_data->floor_color));
    else if (ft_strncmp(line, "C ", 2) == 0)
        return(init_floor_ceiling(line, map_data->ceiling_color));
    return (SUCCESS);
}

int init_texpath(char **map, t_map_data *map_data)
{
    int i;

    i = 0;
    while (map[i] && is_not_map(map[i]))
    {
        if (init_texture(map[i], map_data) != SUCCESS)
            return (1);
        i++;
    }
    return (SUCCESS);
}

int check_if_init(t_map_data *map_data)
{
    if (map_data->no_texture == NULL || map_data->so_texture == NULL ||
        map_data->we_texture == NULL || map_data->ea_texture == NULL ||
        !map_data->floor_color[0]|| !map_data->ceiling_color[0])
        return (1);
    return (SUCCESS);
}

int main_mcheck(t_map_data *map_data)
{
	if(init_texpath(map_data->map, map_data) != SUCCESS)
	{
		// ft_printf_fd(2, "Invalid texture path\n");
		return(1);
	}
	if(check_if_init(map_data) != SUCCESS)
	{
        ft_printf_fd(2, "Error\nNot all texture paths or colors are initialized\n");
		return(1);
	}
	if(check_map(map_data) != SUCCESS)
	{
		printf("Test\n");
	}

	return(SUCCESS);
}

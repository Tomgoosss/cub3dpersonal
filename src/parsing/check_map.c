#include "../../libs/libft/include/libft.h"
#include "../../include/cub3D.h"

int is_not_map(char *line)
{
	if (!line || line[0] == '\0' || line[0] == '\n')
		return (1);
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (*line == '\0' || *line == '\n')
		return (1);
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

int init_path(char *line, char **texture)
{
    int fd;

    while (*line && *line != ' ')
        line++;
    while (*line && *line == ' ')
        line++;
    *texture = ft_strdup(line);
    if (*texture == NULL)
        return (0);
    fd = open(*texture, O_RDONLY);
    if (fd == -1)
    {
        free(*texture);
        return (0);
    }
    close(fd);
    return (1);
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
    // else if (ft_strncmp(line, "F ", 2) == 0)
    //     return(init_floor(line));
    // else if (ft_strncmp(line, "C ", 2) == 0)
    //     return(init_ceiling(line));
    return (1);
}

int init_texpath(char **map, t_map_data **map_data)
{
    for (int i = 0; map[i]; i++)
    {
        if (init_texture(map[i], *map_data) != 1)
            return (0);
    }
    return (1);
}

int main_mcheck(t_map_data *map_data)
{
	int i;

	i = 0;
	if(init_texpath(map_data->map, &map_data) != SUCCESS)
	{
		ft_printf_fd(2, "Error\nInvalid texture path\n");
		return(1);
	}
	printf("%s\n", map_data->no_texture);
	printf("%s\n", map_data->so_texture);
	printf("%s\n", map_data->ea_texture);
	printf("%s\n", map_data->we_texture);
	return(SUCCESS);
}
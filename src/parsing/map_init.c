#include "../../libs/libft/include/libft.h"
#include "../../include/cub3D.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int check_i_map(char **map) {
    int i;
    i = 0;
    while (map[i] && is_not_map(map[i]))
        i++;
    return (i);
}

int is_valid_map_char(char c) {
    return c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\t';
}

void cam_xy(int y, int x, char var, t_map_data *map_data)
{
	map_data->starting[0] = y;
	map_data->starting[1] = x;
	if (var == 'N') 
	{
		map_data->cam_vieuw[0] = 0;
		map_data->cam_vieuw[1] = -1;
    }
    else if (var == 'S') 
	{
		map_data->cam_vieuw[0] = 0;
		map_data->cam_vieuw[1] = 1;
	}
    else if (var == 'E') 
	{
		map_data->cam_vieuw[0] = 1;
		map_data->cam_vieuw[1] = 0;
    }    
	else if (var == 'W') 
	{
		map_data->cam_vieuw[0] = -1;
		map_data->cam_vieuw[1] = 0;
    }
}


int has_valid_starting_position(char **map, int map_height, t_map_data *map_data) {
    int x = 0;
    int y = 0;
    int start_count = 0;
	
    while (y < map_height) {
        x = 0;
        while (map[y][x]) {
            if (map[y][x] == 'N') 
			{
                cam_xy(y, x, 'N', map_data);
                start_count++;
            }
            else if (map[y][x] == 'S') 
			{
                cam_xy(y, x, 'S', map_data);
                start_count++;
            }
            else if (map[y][x] == 'E') 
			{
                cam_xy(y, x, 'E', map_data);
                start_count++;
            }
            else if (map[y][x] == 'W') 
			{
                cam_xy(y, x, 'W', map_data);
                start_count++;
            }
			if(start_count > 1)
				return(1);
            x++;
        }
        y++;
    }
	printf("test x = %d\n test y = %d\n", map_data->starting[1], map_data->starting[0]);
	return(SUCCESS);
}

int check_valid_char(char **map, int map_height, int i) {
    int y;
    int x;

    y = 0;
    x = 0;
    while (y < map_height) {
        x = 0;
        while (map[i + y][x]) {
            if (!is_valid_map_char(map[i + y][x]))
                return 1;
            x++;
        }
        y++;
    }
    return SUCCESS;
}

int check_enclosed_zeros(char **map, int map_height) {
    int i = 0;
    int j;
    int map_width;

    while (i < map_height) {
        j = 0;
        map_width = strlen(map[i]);

        while (j < map_width) {
            if (map[i][j] == '0') {
                if (i > 0 && (map[i - 1][j] == ' ' || map[i - 1][j] == '\t'))
                    return 1;
                if (i < map_height - 1 && (map[i + 1][j] == ' ' || map[i + 1][j] == '\t'))
                    return 1;
                if (j > 0 && (map[i][j - 1] == ' ' || map[i][j - 1] == '\t'))
                    return 1;
                if (j < map_width - 1 && (map[i][j + 1] == ' ' || map[i][j + 1] == '\t'))
                    return 1;
                if (i > 0 && j > 0 && (map[i - 1][j - 1] == ' ' || map[i - 1][j - 1] == '\t'))
                    return 1;
                if (i > 0 && j < map_width - 1 && (map[i - 1][j + 1] == ' ' || map[i - 1][j + 1] == '\t'))
                    return 1;
                if (i < map_height - 1 && j > 0 && (map[i + 1][j - 1] == ' ' || map[i + 1][j - 1] == '\t'))
                    return 1;
                if (i < map_height - 1 && j < map_width - 1 && (map[i + 1][j + 1] == ' ' || map[i + 1][j + 1] == '\t'))
                    return 1;
            }
            j++;
        }
        i++;
    }
    return SUCCESS;
}

int longest_line(char **map) {
    int i = 0;
    int max_length = 0;
    int temp_length;

    while (map[i]) 
	{
        temp_length = strlen(map[i]);
        if (temp_length > max_length)
            max_length = temp_length;
        i++;
    }
    return max_length;
}

char *map_zero_fill(int length) {
    char *line = (char *)malloc((length + 1) * sizeof(char));
    if (!line) 
	{
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }
    int i = 0;
    while (i < length) {
        line[i] = ' ';
        i++;
    }
    line[length] = '\0';
    return line;
}

char **fill_map(char **oldmap, int height) {
    int i;
    int l;
	int j;

	i = 0;
	l = longest_line(oldmap) + 2;
    char **newmap = (char **)malloc((height + 3) * sizeof(char *));
    if (newmap == NULL) 
	{
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }
    newmap[0] = map_zero_fill(l);
    while (i < height) 
	{
        newmap[i + 1] = (char *)malloc((l + 1) * sizeof(char));
        if (newmap[i + 1] == NULL) {
            perror("Malloc failed");
            exit(EXIT_FAILURE);
        }
        newmap[i + 1][0] = ' ';
        j = 0;
        while (oldmap[i][j]) {
            newmap[i + 1][j + 1] = oldmap[i][j];
            j++;
        }
        while (j < l - 1) {
            newmap[i + 1][j + 1] = ' ';
            j++;
        }
        newmap[i + 1][l - 1] = ' ';
        newmap[i + 1][l] = '\0';
        i++;
    }
    newmap[height + 1] = map_zero_fill(l);
    newmap[height + 2] = NULL;
    return newmap;
}

int is_surrounded_by_walls(char **map, int map_height) 
{
	char **temp_map;

    temp_map = fill_map(map, map_height);
    if (check_enclosed_zeros(temp_map, map_height + 2) != SUCCESS)
	{
		ft_free_matrix(temp_map);
        return 1;
	}
	ft_free_matrix(temp_map);
    return SUCCESS;
}

int check_map(t_map_data *map_data) {
    int i;
    int map_height;

    i = check_i_map(map_data->map);
    map_height = 0;
    while (map_data->map[i + map_height])
        map_height++;
    if (check_valid_char(map_data->map, map_height, i))
        return 1;
    if (has_valid_starting_position(map_data->map + i, map_height, map_data) != SUCCESS)
        return 1;
    if (is_surrounded_by_walls(map_data->map + i, map_height) != SUCCESS) {
        printf("Map is not surrounded by walls\n");
        return 1;
    }

    return SUCCESS;
}
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

int has_valid_starting_position(char **map, int map_height) {
    int x = 0;
    int y = 0;
    int start_count = 0;

    while (y < map_height) {
        x = 0;
        while (map[y][x]) {
            if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W') {
                start_count++;
            }
            x++;
        }
        y++;
    }
    return start_count == 1;
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

int check_borders(char **map, int map_height) {
    int i = 0;

    while (map[0][i]) {
        if (map[0][i] != '1' && map[0][i] != ' ' && map[0][i] != '\t')
            return 1;
        i++;
    }
    i = 0;
    while (map[map_height - 1][i]) 
	{
        if (map[map_height - 1][i] != '1' && map[map_height - 1][i] != ' ' && map[map_height - 1][i] != '\t')
            return 1;
        i++;
    }
    i = 0;
    while (i < map_height) {
        int map_width = ft_strlen(map[i]);
        int left = 0;
        while (map[i][left] == ' ' || map[i][left] == '\t')
            left++;
        if (map[i][left] != '1')
            return 1;
        int right = map_width - 1;
        while (right >= 0 && (map[i][right] == ' ' || map[i][right] == '\t'))
            right--;
        if (map[i][right] != '1')
            return 1;
        i++;
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
            if (map[i][j] == '0') 
			{
                if (i > 0 && (map[i - 1][j] == ' ' || map[i - 1][j] == '\t'))
                    return 1;
                if (i < map_height - 1 && (map[i + 1][j] == ' ' || map[i + 1][j] == '\t'))
                    return 1;
                if (j > 0 && (map[i][j - 1] == ' ' || map[i][j - 1] == '\t'))
                    return 1;
                if (j < map_width - 1 && (map[i][j + 1] == ' ' || map[i][j + 1] == '\t'))
                    return 1;
            }
            j++;
        }
        i++;
    }
    return SUCCESS;
}

int is_surrounded_by_walls(char **map, int map_height) 
{
    if (check_borders(map, map_height) != SUCCESS)
        return 1;
    if (check_enclosed_zeros(map, map_height) != SUCCESS)
        return 1;
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
    if (has_valid_starting_position(map_data->map + i, map_height) != 1)
        return 1;
    if (is_surrounded_by_walls(map_data->map + i, map_height) != SUCCESS) {
        printf("Map is not surrounded by walls\n");
        return 1;
    }

    return SUCCESS;
}
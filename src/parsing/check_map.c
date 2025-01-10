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

int path_init

int texture(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		
	else if (ft_strncmp(line, "SO ", 3) == 0)

	else if (ft_strncmp(line, "WE ", 3) == 0)
		
	else if (ft_strncmp(line, "EA ", 3) == 0)
		
	else if (ft_strncmp(line, "F ", 2) == 0)

	else if (ft_strncmp(line, "C ", 2) == 0)
	
	
}

int init_texpath(char **map)
{
	int i;

	i = 0;
	while(is_not_map(map[i]))
	{
		texture(map[i])
		i++;
	}
	printf("test mapcheck %d\n", i);
	return(SUCCESS);
}

int main_mcheck(t_map_data map_data)
{
	int i;

	i = 0;
	if(init_texpath(map_data.map) != SUCCESS)
	{
		ft_printf_fd(2, "Error\nInvalid texture path\n");
		return(1);
	}
	return(SUCCESS);
}
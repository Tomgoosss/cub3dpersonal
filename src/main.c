/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomgoossens <tomgoossens@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:12:48 by qvan-ste          #+#    #+#             */
/*   Updated: 2025/01/24 14:44:28 by tomgoossens      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/libft/include/libft.h"
#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	t_map_data	map_data;

	if (argc != 2)
	{
		ft_printf_fd(2, "Error\nIncorrect number of argments\n");
		return (1);
	}
	if (check_extension(argv[1]) != 0)
	{
		ft_printf_fd(2, "Error\nIncorrect file format\n");
		return (1);
	}
	if (create_map(argv[1], &map_data) != SUCCESS)
		return (1);
	if	(main_mcheck(&map_data) != SUCCESS)
	{
		// ft_printf_fd(2, "Error\nMap not valid\n");
		return(1);
	}
	// ft_print_matrix(map_data .map);
	ft_free_matrix(map_data.map);
	return (0);
}

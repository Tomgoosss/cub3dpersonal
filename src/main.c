/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgoossen <tgoossen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 16:12:48 by qvan-ste          #+#    #+#             */
/*   Updated: 2025/02/11 15:35:07 by tgoossen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"
#include "../libs/libft/include/libft.h"

int	main(int argc, char **argv)
{
	t_data			data;

	ft_bzero(&data, sizeof(t_data));
	if (validate_input(argc, argv) != SUCCESS)
	{
		return (FAILURE);
	}
	if (init_data(&data, argv[1]) != SUCCESS)
	{
		free_data(data);
		return (FAILURE);
	}
	execute(&data);
	free_data(data);
}

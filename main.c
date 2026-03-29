/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:16:35 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/17 13:16:35 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
	{
		ft_putendl_fd("Usage: ./cub3D <scene.cub>", STDOUT_FILENO);
		return (EXIT_FAILURE);
	}
	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		exit_error(NULL, "Malloc for cub failed.");
	init_cub(argv[1], cub);
	init_window(cub);
	return (0);
}

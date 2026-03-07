/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:09:41 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/26 15:09:44 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	free_gnl(int fd, char *line, char *last_line)
{
	char	*gnl;

	free(line);
	free(last_line);
	gnl = get_next_line(fd);
	while (gnl)
	{
		free(gnl);
		gnl = get_next_line(fd);
	}
}

static void	free_mlx(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (cub->tex[i].ptr)
			mlx_destroy_image(cub->mlx, cub->tex[i].ptr);
		i++;
	}
	if (cub->frame.ptr)
		mlx_destroy_image(cub->mlx, cub->frame.ptr);
	if (cub->win)
		mlx_destroy_window(cub->mlx, cub->win);
	if (cub->mlx)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
	}
}

void	free_cub(t_cub *cub)
{
	int	i;

	if (!cub)
		return ;
	i = 0;
	while (i < 4)
	{
		if (cub->tex_paths[i])
			free(cub->tex_paths[i]);
		i++;
	}
	if (cub->map)
	{
		i = 0;
		while (i < cub->map_h)
		{
			if (cub->map[i])
				free(cub->map[i]);
			i++;
		}
		free(cub->map);
	}
	free_mlx(cub);
	free(cub);
}

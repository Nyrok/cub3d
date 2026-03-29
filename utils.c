/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 13:16:35 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/22 17:45:01 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

int	safe_open(t_cub *cub, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		exit_error(cub, "Can't open the file.");
	return (fd);
}

void	safe_close(t_cub *cub, int fd)
{
	if (close(fd) == -1)
		exit_error(cub, "Can't close the file.");
}

int	is_open(t_cub *cub, int y, int x)
{
	if (y < 0 || y >= cub->map_h)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(cub->map[y]))
		return (1);
	if (cub->map[y][x] == ' ')
		return (1);
	return (0);
}

int	is_wall(t_cub *cub, int x, int y)
{
	if (y < 0 || y >= cub->map_h)
		return (1);
	if (x < 0 || x >= (int)ft_strlen(cub->map[y]))
		return (1);
	if (cub->map[y][x] == '1' || cub->map[y][x] == ' ')
		return (1);
	return (0);
}

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

int	parse_color(t_cub *cub, char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	while (*str == ' ' || *str == '\t')
		str++;
	rgb = ft_split(str, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		exit_error(cub, "Invalid color format.");
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free(rgb[0]);
	free(rgb[1]);
	free(rgb[2]);
	free(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		exit_error(cub, "Color values must be 0-255.");
	return ((r << 16) | (g << 8) | b);
}

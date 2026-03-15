/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:16:35 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/17 13:16:35 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

static void	check_chars(t_cub *cub)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (cub->map[y][x])
		{
			c = cub->map[y][x];
			if (c != '0' && c != '1' && c != 'N' && c != 'S'
				&& c != 'E' && c != 'W' && c != ' ')
				exit_error(cub, "Invalid character in map.");
			x++;
		}
		y++;
	}
}

static int	init_player(t_cub *cub, int x, int y, char c)
{
	static const double	d[4][4] = {
	{0, -1, 0.66, 0},
	{0, 1, -0.66, 0},
	{1, 0, 0, 0.66},
	{-1, 0, 0, -0.66}
	};
	int					i;

	i = (c == 'S') + 2 * (c == 'E') + 3 * (c == 'W');
	cub->player.pos_x = x + 0.5;
	cub->player.pos_y = y + 0.5;
	cub->player.dir_x = d[i][0];
	cub->player.dir_y = d[i][1];
	cub->player.plane_x = d[i][2];
	cub->player.plane_y = d[i][3];
	return (1);
}

static void	check_player(t_cub *cub)
{
	int		count;
	int		y;
	int		x;
	char	c;

	count = 0;
	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (cub->map[y][x])
		{
			c = cub->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				count += init_player(cub, x, y, c);
			x++;
		}
		y++;
	}
	if (count != 1)
		exit_error(cub, "Map must have exactly one player spawn.");
}

static void	check_closed(t_cub *cub)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < cub->map_h)
	{
		x = 0;
		while (cub->map[y][x])
		{
			c = cub->map[y][x];
			if (c == '0' || c == 'N' || c == 'S'
				|| c == 'E' || c == 'W')
			{
				if (is_open(cub, y - 1, x) || is_open(cub, y + 1, x)
					|| is_open(cub, y, x - 1) || is_open(cub, y, x + 1))
					exit_error(cub, "Map is not closed/surrounded by walls.");
			}
			x++;
		}
		y++;
	}
}

void	validate_cub(t_cub *cub)
{
	int	i;
	int	fd;

	if (!cub->tex_paths[0] || !cub->tex_paths[1]
		|| !cub->tex_paths[2] || !cub->tex_paths[3])
		exit_error(cub, "Missing texture path(s) in .cub file.");
	if (cub->floor_color < 0 || cub->ceil_color < 0)
		exit_error(cub, "Missing floor or ceiling color in .cub file.");
	i = 0;
	while (i < 4)
	{
		fd = open(cub->tex_paths[i], O_RDONLY);
		if (fd == -1)
			exit_error(cub, "Texture file not found.");
		close(fd);
		i++;
	}
	if (!cub->map || cub->map_h == 0)
		exit_error(cub, "Map is empty.");
	check_chars(cub);
	check_player(cub);
	check_closed(cub);
}

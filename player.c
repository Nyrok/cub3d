/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:16:35 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/17 13:16:35 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	move_forward(t_cub *cub)
{
	double	nx;
	double	ny;

	nx = cub->player.pos_x + cub->player.dir_x * MOVE_SPEED;
	ny = cub->player.pos_y + cub->player.dir_y * MOVE_SPEED;
	if (!is_wall(cub, (int)nx, (int)cub->player.pos_y))
		cub->player.pos_x = nx;
	if (!is_wall(cub, (int)cub->player.pos_x, (int)ny))
		cub->player.pos_y = ny;
}

void	move_backward(t_cub *cub)
{
	double	nx;
	double	ny;

	nx = cub->player.pos_x - cub->player.dir_x * MOVE_SPEED;
	ny = cub->player.pos_y - cub->player.dir_y * MOVE_SPEED;
	if (!is_wall(cub, (int)nx, (int)cub->player.pos_y))
		cub->player.pos_x = nx;
	if (!is_wall(cub, (int)cub->player.pos_x, (int)ny))
		cub->player.pos_y = ny;
}

void	strafe_left(t_cub *cub)
{
	double	nx;
	double	ny;

	nx = cub->player.pos_x - cub->player.plane_x * MOVE_SPEED;
	ny = cub->player.pos_y - cub->player.plane_y * MOVE_SPEED;
	if (!is_wall(cub, (int)nx, (int)cub->player.pos_y))
		cub->player.pos_x = nx;
	if (!is_wall(cub, (int)cub->player.pos_x, (int)ny))
		cub->player.pos_y = ny;
}

void	strafe_right(t_cub *cub)
{
	double	nx;
	double	ny;

	nx = cub->player.pos_x + cub->player.plane_x * MOVE_SPEED;
	ny = cub->player.pos_y + cub->player.plane_y * MOVE_SPEED;
	if (!is_wall(cub, (int)nx, (int)cub->player.pos_y))
		cub->player.pos_x = nx;
	if (!is_wall(cub, (int)cub->player.pos_x, (int)ny))
		cub->player.pos_y = ny;
}

void	rotate_player(t_cub *cub, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir_x;
	cub->player.dir_x = cub->player.dir_x * cos(angle)
		- cub->player.dir_y * sin(angle);
	cub->player.dir_y = old_dir_x * sin(angle)
		+ cub->player.dir_y * cos(angle);
	old_plane_x = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(angle)
		- cub->player.plane_y * sin(angle);
	cub->player.plane_y = old_plane_x * sin(angle)
		+ cub->player.plane_y * cos(angle);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 14:27:52 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/22 14:27:54 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

static void	init_ray(t_cub *cub, t_ray *ray, int x)
{
	double	cam_x;

	cam_x = 2.0 * x / WIN_W - 1.0;
	ray->dir_x = cub->player.dir_x + cub->player.plane_x * cam_x;
	ray->dir_y = cub->player.dir_y + cub->player.plane_y * cam_x;
	ray->map_x = (int)cub->player.pos_x;
	ray->map_y = (int)cub->player.pos_y;
	if (ray->dir_x == 0.0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0.0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1.0 / ray->dir_y);
}

static void	calc_step(t_ray *ray, t_player *p)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (p->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - p->pos_x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (p->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - p->pos_y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_cub *cub, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cub->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}

static void	get_wall_info(t_ray *ray, t_player *p, t_img *tex)
{
	if (ray->side == 0)
		ray->perp_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WIN_H / ray->perp_dist);
	ray->draw_start = WIN_H / 2 - ray->line_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = WIN_H / 2 + ray->line_height / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
	if (ray->side == 0)
		ray->wall_x = p->pos_y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_x = p->pos_x + ray->perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = tex->width - ray->tex_x - 1;
}

void	cast_rays(t_cub *cub)
{
	t_ray	ray;
	int		x;
	int		tex_idx;

	x = 0;
	while (x < WIN_W)
	{
		init_ray(cub, &ray, x);
		calc_step(&ray, &cub->player);
		perform_dda(cub, &ray);
		tex_idx = TEX_NO;
		if (ray.side == 1 && ray.step_y > 0)
			tex_idx = TEX_SO;
		else if (ray.side == 0 && ray.step_x > 0)
			tex_idx = TEX_EA;
		else if (ray.side == 0 && ray.step_x < 0)
			tex_idx = TEX_WE;
		get_wall_info(&ray, &cub->player, &cub->tex[tex_idx]);
		draw_column(cub, &ray, x);
		x++;
	}
}

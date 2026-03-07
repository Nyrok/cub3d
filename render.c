/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:16:35 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/17 13:16:35 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = img->data + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int	get_tex_pixel(t_img *tex, int x, int y)
{
	char	*src;

	if (x < 0)
		x = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y < 0)
		y = 0;
	if (y >= tex->height)
		y = tex->height - 1;
	src = tex->data + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)src);
}

void	draw_floor_ceiling(t_cub *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_H / 2)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&cub->frame, x, y, cub->ceil_color);
			x++;
		}
		y++;
	}
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			put_pixel(&cub->frame, x, y, cub->floor_color);
			x++;
		}
		y++;
	}
}

void	draw_column(t_cub *cub, t_ray *ray, int x)
{
	int		tex_idx;
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;

	tex_idx = TEX_NO;
	if (ray->side == 1 && ray->step_y > 0)
		tex_idx = TEX_SO;
	else if (ray->side == 0 && ray->step_x > 0)
		tex_idx = TEX_EA;
	else if (ray->side == 0 && ray->step_x < 0)
		tex_idx = TEX_WE;
	step = 1.0 * cub->tex[tex_idx].height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (cub->tex[tex_idx].height - 1);
		tex_pos += step;
		put_pixel(&cub->frame, x, y,
			get_tex_pixel(&cub->tex[tex_idx], ray->tex_x, tex_y));
		y++;
	}
}

void	render_frame(t_cub *cub)
{
	draw_floor_ceiling(cub);
	cast_rays(cub);
}

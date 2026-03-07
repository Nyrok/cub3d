/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:18:00 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/17 13:19:13 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <math.h>
# include "./libft.h"
# include "./get_next_line_bonus.h"
# include "../minilibx-linux/mlx.h"
# define WIN_W 1280
# define WIN_H 720
# define TEX_NO 0
# define TEX_SO 1
# define TEX_WE 2
# define TEX_EA 3
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
# define MAP_FILE_EXT ".cub"

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_img
{
	void	*ptr;
	char	*data;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_cub
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_h;
	int			map_w;
	char		*tex_paths[4];
	t_img		tex[4];
	t_img		frame;
	int			floor_color;
	int			ceil_color;
	t_player	player;
	t_keys		keys;
}	t_cub;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
}	t_ray;

void	init_cub(char *path, t_cub *cub);
void	exit_error(t_cub *cub, char *message);
int		exit_game(t_cub *cub);
void	cast_rays(t_cub *cub);
int		safe_open(t_cub *cub, char *path);
void	safe_close(t_cub *cub, int fd);
void	free_cub(t_cub *cub);
void	free_gnl(int fd, char *line, char *last_line);
int		ft_strcount(char *str, char c);
void	validate_cub(t_cub *cub);
void	init_window(t_cub *cub);
void	render_frame(t_cub *cub);
void	draw_column(t_cub *cub, t_ray *ray, int x);
void	put_pixel(t_img *img, int x, int y, int color);
void	draw_floor_ceiling(t_cub *cub);
int		get_tex_pixel(t_img *tex, int x, int y);
void	move_forward(t_cub *cub);
void	move_backward(t_cub *cub);
void	strafe_left(t_cub *cub);
void	strafe_right(t_cub *cub);
void	rotate_player(t_cub *cub, double angle);

#endif

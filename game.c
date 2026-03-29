/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 18:21:58 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/26 18:21:59 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

static void	load_textures(t_cub *cub)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		cub->tex[i].ptr = mlx_xpm_file_to_image(cub->mlx,
				cub->tex_paths[i], &cub->tex[i].width, &cub->tex[i].height);
		if (!cub->tex[i].ptr)
			exit_error(cub, "Failed to load texture.");
		cub->tex[i].data = mlx_get_data_addr(cub->tex[i].ptr,
				&cub->tex[i].bpp, &cub->tex[i].line_len, &cub->tex[i].endian);
		i++;
	}
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == 119 || keycode == 65362)
		cub->keys.w = 1;
	else if (keycode == 115 || keycode == 65364)
		cub->keys.s = 1;
	else if (keycode == 97)
		cub->keys.a = 1;
	else if (keycode == 100)
		cub->keys.d = 1;
	else if (keycode == 65361)
		cub->keys.left = 1;
	else if (keycode == 65363)
		cub->keys.right = 1;
	else if (keycode == 65307)
		exit_game(cub);
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == 119 || keycode == 65362)
		cub->keys.w = 0;
	else if (keycode == 115 || keycode == 65364)
		cub->keys.s = 0;
	else if (keycode == 97)
		cub->keys.a = 0;
	else if (keycode == 100)
		cub->keys.d = 0;
	else if (keycode == 65361)
		cub->keys.left = 0;
	else if (keycode == 65363)
		cub->keys.right = 0;
	return (0);
}

int	game_loop(t_cub *cub)
{
	if (cub->keys.w)
		move_forward(cub);
	if (cub->keys.s)
		move_backward(cub);
	if (cub->keys.a)
		strafe_left(cub);
	if (cub->keys.d)
		strafe_right(cub);
	if (cub->keys.left)
		rotate_player(cub, -ROT_SPEED);
	if (cub->keys.right)
		rotate_player(cub, ROT_SPEED);
	render_frame(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->frame.ptr, 0, 0);
	return (0);
}

void	init_window(t_cub *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
		exit_error(cub, "Cannot initialize mlx.");
	cub->win = mlx_new_window(cub->mlx, WIN_W, WIN_H, "cub3D");
	if (!cub->win)
		exit_error(cub, "Cannot create window.");
	cub->frame.ptr = mlx_new_image(cub->mlx, WIN_W, WIN_H);
	if (!cub->frame.ptr)
		exit_error(cub, "Failed to create frame image.");
	cub->frame.data = mlx_get_data_addr(cub->frame.ptr,
			&cub->frame.bpp, &cub->frame.line_len, &cub->frame.endian);
	load_textures(cub);
	mlx_hook(cub->win, 2, 1L << 0, key_press, cub);
	mlx_hook(cub->win, 3, 1L << 1, key_release, cub);
	mlx_hook(cub->win, 17, 0, exit_game, cub);
	mlx_loop_hook(cub->mlx, game_loop, cub);
	mlx_loop(cub->mlx);
}

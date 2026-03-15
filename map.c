/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonte <hkonte@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:16:35 by hkonte            #+#    #+#             */
/*   Updated: 2025/04/17 13:16:35 by hkonte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/cub3d.h"

static void	parse_element(t_cub *cub, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		cub->tex_paths[TEX_NO] = ft_strtrim(line + 3, " \t\n");
	else if (!ft_strncmp(line, "SO ", 3))
		cub->tex_paths[TEX_SO] = ft_strtrim(line + 3, " \t\n");
	else if (!ft_strncmp(line, "WE ", 3))
		cub->tex_paths[TEX_WE] = ft_strtrim(line + 3, " \t\n");
	else if (!ft_strncmp(line, "EA ", 3))
		cub->tex_paths[TEX_EA] = ft_strtrim(line + 3, " \t\n");
	else if (!ft_strncmp(line, "F ", 2))
		cub->floor_color = parse_color(cub, line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		cub->ceil_color = parse_color(cub, line + 2);
	else
		exit_error(cub, "Unknown element in .cub file.");
}

static int	all_elements_set(t_cub *cub)
{
	return (cub->tex_paths[0] && cub->tex_paths[1]
		&& cub->tex_paths[2] && cub->tex_paths[3]
		&& cub->floor_color >= 0 && cub->ceil_color >= 0);
}

static void	parse_map_line(t_cub *cub, char *line, int fd)
{
	char	*trimmed;
	char	**new_map;
	int		len;

	while (line)
	{
		trimmed = ft_strtrim(line, "\n");
		free(line);
		len = ft_strlen(trimmed);
		if (len > cub->map_w)
			cub->map_w = len;
		new_map = ft_calloc(cub->map_h + 2, sizeof(char *));
		if (!new_map)
			exit_error(cub, "Malloc failed for map.");
		ft_memcpy(new_map, cub->map, cub->map_h * sizeof(char *));
		new_map[cub->map_h] = trimmed;
		free(cub->map);
		cub->map = new_map;
		cub->map_h++;
		line = get_next_line(fd);
	}
}

static void	parse_file(t_cub *cub, int fd)
{
	char	*line;
	char	*trimmed;

	line = get_next_line(fd);
	while (line)
	{
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (all_elements_set(cub))
		{
			trimmed = ft_strtrim(line, "\n");
			free(line);
			parse_map_line(cub, trimmed, fd);
			return ;
		}
		parse_element(cub, line);
		free(line);
		line = get_next_line(fd);
	}
}

void	init_cub(char *path, t_cub *cub)
{
	int		fd;
	size_t	ext_len;
	size_t	path_len;

	if (!cub)
		exit_error(NULL, "Malloc for cub failed.");
	ext_len = ft_strlen(MAP_FILE_EXT);
	path_len = ft_strlen(path);
	if (path_len < ext_len
		|| ft_strncmp(path + path_len - ext_len, MAP_FILE_EXT, ext_len))
		exit_error(cub, "Map file must end with .cub");
	ft_memset(cub, 0, sizeof(t_cub));
	cub->floor_color = -1;
	cub->ceil_color = -1;
	fd = safe_open(cub, path);
	parse_file(cub, fd);
	safe_close(cub, fd);
	validate_cub(cub);
}

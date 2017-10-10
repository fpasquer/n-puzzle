/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 11:30:45 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/10 14:24:20 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

#define C_EMPTY 0
#define C_BACKGROUND 1
#define C_TEXT 2
#define C_BORDER 3

static unsigned char		g_color[][4] =
{
	{0xff, 0xff, 0xff, 1},
	{0x8e, 0x9e, 0xe6, 1},
	{0xff, 0xff, 0xff, 1},
	{0xff, 0xff, 0xff, 1}
};

static bool					draw_grid_print(t_mlx_npuzzle *mlx, int const y,
		int const x)
{
	char					str[2];
	int						tmp;
	int						k;
	int						color_text;

	if (mlx == NULL || mlx->grid == NULL || mlx->grid->grid == NULL ||
			mlx->data == NULL)
		return (false);
	str[1] = '\0';
	color_text = ft_rgba(g_color[C_TEXT][0], g_color[C_TEXT][1],
		g_color[C_TEXT][2], g_color[C_TEXT][3]);
	k = 0;
	tmp = mlx->grid->grid[y][x];
	while (tmp != 0)
	{
		str[0] = (char)tmp % 10 + '0';
		mlx_string_put(mlx->mlx, mlx->win, x * NB_PIX_EACH_BOX +
				NB_PIX_EACH_BOX - 20 - k * 10, y * NB_PIX_EACH_BOX + 10,
				color_text, str);
		tmp /= 10;
		k++;
	}
	return (true);
}

static int					draw_grid_loop(t_mlx_npuzzle *mlx, int const end,
		int const y, int const x)
{
	int						i;
	int						j;
	int						color_back;
	int						color_border;

	if (mlx == NULL || mlx->grid == NULL || mlx->grid->grid == NULL ||
			mlx->data == NULL)
		return (-1);
	j = mlx->grid->grid[y][x] == 0 ? C_EMPTY : C_BACKGROUND;
	color_back = ft_rgba(g_color[j][0], g_color[j][1],
		g_color[j][2], g_color[j][3]);
	color_border = ft_rgba(g_color[C_BORDER][0], g_color[C_BORDER][1],
		g_color[C_BORDER][2], g_color[C_BORDER][3]);
	i = -1;
	while (++i < end)
		mlx->data[j][i] = (i < NB_PIX_EACH_BOX || i >= end - NB_PIX_EACH_BOX ||
				(i % NB_PIX_EACH_BOX) == 0 || (i % NB_PIX_EACH_BOX) ==
				NB_PIX_EACH_BOX - 1) ? color_border : color_back;
	if (mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img[j],
			x * NB_PIX_EACH_BOX, y * NB_PIX_EACH_BOX) == false)
		return (false);
	if (mlx->grid->grid[y][x] != 0)
		return (draw_grid_print(mlx, y, x));
	return (true);
}

int							draw_grid(t_mlx_npuzzle *mlx)
{
	int						y;
	int						x;
	int						end;

	if (mlx == NULL || mlx->grid == NULL || mlx->grid->grid == NULL ||
			mlx->data == NULL)
		return (-1);
	mlx_clear_window(mlx->mlx, mlx->win);
	y = 0;
	end = NB_PIX_EACH_BOX * NB_PIX_EACH_BOX;
	while (y < mlx->grid->x_y)
	{
		x = 0;
		while (x < mlx->grid->x_y)
			if (draw_grid_loop(mlx, end, y, x++) != true)
				return (false);
		y++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_dfs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 10:51:25 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/10 09:26:46 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

int							g_grid_3x3[3][3] =
{
	{1, 2, 3},
	{8, 0, 4},
	{7, 6, 5}
};

int							g_grid_4x4[4][4] =
{
	{1, 2, 3, 4},
	{12, 13, 14, 5},
	{11, 0, 15, 6},
	{10, 9, 8, 7}
};

int							g_grid_5x5[5][5] =
{
	{1, 2, 3, 4, 5},
	{16, 17, 18, 19, 6},
	{15, 24, 0, 20, 7},
	{14, 23, 22, 21, 8},
	{13, 12, 11, 10, 9}
};

bool						get_coord_zero(t_grid *grid, t_coord *coord)
{
	if (grid->grid == NULL || coord == NULL)
		return (false);
	for (coord->y = 0; coord->y < grid->x_y; coord->y++)
		for (coord->x = 0; coord->x < grid->x_y; coord->x++)
			if (grid->grid[coord->y][coord->x] == EMPTY)
				return (true);
	return (false);
}

int							get_move_possible(t_grid *grid, int const y_zero,
	int const x_zero)
{
	int						move;

	move = FLAG_NONE;
	if (y_zero > 0 && !(y_zero - 1 == grid->prev.y && x_zero == grid->prev.x))
		move = (move | FLAG_TOP);
	if (y_zero + 1 < grid->x_y && !(y_zero + 1 == grid->prev.y && x_zero == grid->prev.x))
		move = (move | FLAG_BOTTOM);
	if (x_zero > 0 && !(y_zero == grid->prev.y && x_zero - 1 == grid->prev.x))
		move = (move | FLAG_LEFT);
	if (x_zero + 1 < grid->x_y && !(y_zero == grid->prev.y && x_zero + 1 == grid->prev.x))
		move = (move | FLAG_RIGHT);
	return (move);
}

int							is_Done(t_grid *grid)
{
	int						y;
	int						x;
	int						ret;

	if (grid == NULL || grid->grid == NULL)
		return (-1);
	for (y = 0, ret = 0; y < grid->x_y; y++)
		for (x = 0; x < grid->x_y; x++)
			if (grid->x_y == 3 && g_grid_3x3[y][x] == grid->grid[y][x])
				ret++;
			else if (grid->x_y == 4 && g_grid_4x4[y][x] == grid->grid[y][x])
				ret++;
			else if (grid->x_y == 5 && g_grid_5x5[y][x] == grid->grid[y][x])
				ret++;
	return (ret);
}
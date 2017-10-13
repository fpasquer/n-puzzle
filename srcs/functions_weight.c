/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_weight.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:13:02 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/13 11:03:06 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					get_weight_init_value(t_grid *grid,
		int const y_coord, int const x_coord)
{
	int						y;
	int						x;
	int						ret1;
	int						ret2;
	int						linear_c;

	if (grid == NULL || grid->grid == NULL)
		return (INT_MIN);
	if (get_coord_value(grid->grid[y_coord][x_coord], grid->x_y, &y, &x) <= 0)
		return (INT_MIN);
	linear_c = 0;
	ret1 = (y > y_coord) ? y - y_coord : y_coord - y;
	ret2 = (x > x_coord) ? x - x_coord : x_coord - x;
	if (ret1 == 0 && x_coord < grid->x_y - 1)
		if (linear_conflict(grid, y_coord, x_coord, &linear_c) != true)
			return (INT_MIN);
	return (ret1 + ret2 + linear_c);
}

static int					in_loop_get_coord_value(t_coord coord_dest[],
		int const x_y, int **y, int **x)
{
	if (y == NULL || *y == NULL || x == NULL || *x == NULL)
		return (false);
	if (x_y == 3)
	{
		coord_dest[g_grid_3x3[**y][**x]].y = (**y);
		coord_dest[g_grid_3x3[**y][**x]].x = (**x);
	}
	else if (x_y == 4)
	{
		coord_dest[g_grid_4x4[**y][**x]].y = (**y);
		coord_dest[g_grid_4x4[**y][**x]].x = (**x);
	}
	else if (x_y == 5)
	{
		coord_dest[g_grid_5x5[**y][**x]].y = (**y);
		coord_dest[g_grid_5x5[**y][**x]].x = (**x);
	}
	(**x)++;
	return (true);
}

int							get_coord_value(int const value, int const x_y,
		int *y, int *x)
{
	static t_coord			coord_dest[SIZE_FILE_MAX * SIZE_FILE_MAX];
	static int				loop = 0;

	if (y == NULL || x == NULL || value >= SIZE_FILE_MAX * SIZE_FILE_MAX ||
			value < 0)
		return (-1);
	if (loop == 0)
	{
		(*y) = 0;
		while ((*y) < x_y)
		{
			(*x) = 0;
			while ((*x) < x_y)
				if (in_loop_get_coord_value(coord_dest, x_y, &y, &x) == false)
					return (-1);
			(*y)++;
		}
		loop = 1;
	}
	(*y) = coord_dest[value].y;
	(*x) = coord_dest[value].x;
	return (true);
}

int							get_weight_init(t_grid *grid)
{
	int						y;
	int						x;
	int						ret;
	int						tmp;

	if (grid == NULL || grid->grid == NULL)
		return (INT_MIN);
	y = 0;
	ret = 0;
	while (y < grid->x_y)
	{
		x = 0;
		while (x < grid->x_y)
			if (grid->grid[y][x++] != EMPTY)
			{
				if ((tmp = get_weight_init_value(grid, y, x - 1)) == INT_MIN)
					return (INT_MIN);
				ret += tmp;
			}
		y++;
	}
	return (ret);
}

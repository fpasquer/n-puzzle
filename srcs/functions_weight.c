/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_weight.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:13:02 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/20 11:30:13 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static bool					linear_conflict(t_grid *grid, int const y,
	int const x, int *weight)
{
	int						x_curs;
	int						y_dest;
	int						x_dest;

	if (grid == NULL || grid->grid == NULL || weight == NULL)
		return (false);
	for (x_curs = x + 1; x_curs < grid->x_y; x_curs++)
	{
		if (get_coord_value(grid->grid[y][x_curs], grid->x_y, &y_dest, &x_dest)
				<= 0)
			return (false);
		if (y_dest == y && x_dest <= x)
			(*weight) += 2;
	}
	return (true);
}

static int					get_weight_init_value(t_grid *grid, int const
		y_coord, int const x_coord)
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
	return(ret1 + ret2 + linear_c);
}

static int			general_weight(t_grid *grid, int const flag,
		int const y_zero, int const x_zero, int const y_new, int const x_new,
		int weight)
{
	int						y;
	int						x;
	int						ret;
	int						ret1;
	int						ret2;

	if (grid->flag == 0)
		return (flag);
	if (get_coord_value(grid->grid[y_new][x_new], grid->x_y, &y, &x) <= 0)
		return (INT_MIN);
	ret1 = (y > y_zero) ? y - y_zero : y_zero - y;
	ret2 = (x > x_zero) ? x - x_zero : x_zero - x;
	ret = 0;
	if ((grid->flag & F_MANHATTAN) != 0)
	{
		ret += weight;
		ret += ret1 + ret2;
		ret -= (y > y_new) ? y - y_new : y_new - y;
		ret -= (x > x_new) ? x - x_new : x_new - x;
	}
	if ((grid->flag & F_MAL_PLACE) != 0)
		ret += (ret1 + ret2 == 0) ? 1 : 0;
	if ((grid->flag & F_LINEAR_C) != 0 && ret1 == 0 && x_zero < grid->x_y - 1)
		if (linear_conflict(grid, y_zero, x_zero, &ret) != true)
			return (INT_MIN);
	return (ret);
}

int							get_coord_value(int const value, int const x_y,
		int *y, int *x)
{
	static t_coord			coord_dest[SIZE_file_MAX * SIZE_file_MAX];
	static int				loop = 0;

	if (y == NULL || x == NULL || value >= SIZE_file_MAX * SIZE_file_MAX)
		return (-1);
	if (loop == 0)
	{
		for((*y) = 0; (*y) < x_y; (*y)++)
			for (*x = 0; *x < x_y; (*x)++)
				if (x_y == 3)
				{
					coord_dest[g_grid_3x3[*y][*x]].y = (*y);
					coord_dest[g_grid_3x3[*y][*x]].x = (*x);
				}
				else if (x_y == 4)
				{
					coord_dest[g_grid_4x4[*y][*x]].y = (*y);
					coord_dest[g_grid_4x4[*y][*x]].x = (*x);
				}
				else if (x_y == 5)
				{
					coord_dest[g_grid_5x5[*y][*x]].y = (*y);
					coord_dest[g_grid_5x5[*y][*x]].x = (*x);
				}
		loop = 1;
	}
	(*y) = coord_dest[value].y;
	(*x) = coord_dest[value].x;
	return (true);
}

int					get_weight_init(t_grid *grid)
{
	int						y;
	int						x;
	int						ret;
	int						tmp;

	if (grid == NULL || grid->grid == NULL)
		return (INT_MIN);
	for (y = 0, ret = 0; y < grid->x_y; y++)
		for(x = 0; x < grid->x_y; x++)
			if (grid->grid[y][x] != EMPTY)
			{
				if ((tmp = get_weight_init_value(grid, y, x)) == INT_MIN)
					return (INT_MIN);
				ret += tmp;
			}
	return (ret);
}

int							get_weight_top(t_grid *grid, int const y_zero,
		int const x_zero, int weight)
{
	if (grid == NULL || grid->grid == NULL || y_zero - 1 < 0)
		return (INT_MIN);
	return (general_weight(grid, FLAG_TOP, y_zero, x_zero, y_zero - 1, x_zero, 
			weight));
}

int							get_weight_bottom(t_grid *grid, int const y_zero,
		int const x_zero, int weight)
{
	if (grid == NULL || grid->grid == NULL || y_zero + 1 >= grid->x_y)
		return (INT_MIN);
	return (general_weight(grid, FLAG_BOTTOM, y_zero, x_zero, y_zero + 1,
			x_zero, weight));
}

int							get_weight_left(t_grid *grid, int const y_zero,
		int const x_zero, int weight)
{
	if (grid == NULL || grid->grid == NULL || x_zero - 1 < 0)
		return (INT_MIN);
	return (general_weight(grid, FLAG_LEFT, y_zero, x_zero, y_zero, x_zero - 1,
			weight));
}

int							get_weight_right(t_grid *grid, int const y_zero,
		int const x_zero, int weight)
{
	if (grid == NULL || grid->grid == NULL || x_zero + 1 >= grid->x_y)
		return (INT_MIN);
	return (general_weight(grid, FLAG_RIGHT, y_zero, x_zero, y_zero, x_zero + 1,
			weight));
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_weight.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 18:13:02 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/11 14:04:18 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					get_coord_value(int value, int const x_y, int *y,
		int *x)
{
	if (y == NULL || x == NULL)
		return (-1);
	for (*y = 0; *y < x_y; (*y)++)
		for (*x = 0; *x < x_y; (*x)++)
			if (x_y == 3 && value == g_grid_3x3[*y][*x])
				return (1);
			else if (x_y == 4 && value == g_grid_4x4[*y][*x])
				return (1);
			else if (x_y == 5 && value == g_grid_5x5[*y][*x])
				return (1);
	return (0);
}

static int					get_weight_init_value(t_grid *grid, int const y_coord,
	int const x_coord)
{
	int						y;
	int						x;
	int						ret1, ret2;

	if (grid == NULL || grid->grid == NULL)
		return (INT_MIN);
	if (get_coord_value(grid->grid[y_coord][x_coord], grid->x_y, &y, &x) <= 0)
		return (INT_MIN);
	ret1 = (y > y_coord) ? y - y_coord : y_coord - y;
	ret2 = (x > x_coord) ? x - x_coord : x_coord - x;
#ifdef DEBUG
	printf("ret1 = %d, ret2 = %d\n", ret1, ret2);
#endif
	return(ret1 + ret2);
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
		{
			if ((tmp = get_weight_init_value(grid, y, x)) == INT_MIN)
				return (INT_MIN);
			ret += tmp;
		}
	return (ret);
}

int							get_weight_top(t_grid *grid, int const y_zero,
		int const x_zero)
{
	int						y, x, ret1, ret2, ret;

	if (grid == NULL || grid->grid == NULL || y_zero - 1 < 0)
		return (INT_MIN);
	if (grid->flag == 0)
		return (FLAG_TOP);
	if (get_coord_value(grid->grid[y_zero - 1][x_zero], grid->x_y, &y, &x) <= 0)
		return (INT_MIN);
	ret1 = (y > y_zero) ? y - y_zero : y_zero - y;
	ret2 = (x > x_zero) ? x - x_zero : x_zero - x;
	ret = 0;
	if ((grid->flag & F_MANHATTAN) != 0)
		ret += ((grid->x_y - 1) * 2 - ret1 - ret2);
	if ((grid->flag & F_MAL_PLACE) != 0)
		ret += (ret1 + ret2 == 0 ? 1 : 0);
	return (ret);
}

int							get_weight_bottom(t_grid *grid, int const y_zero,
	int const x_zero)
{
	int						y, x, ret1, ret2, ret;

	if (grid == NULL || grid->grid == NULL || y_zero + 1 >= grid->x_y)
		return (INT_MIN);
	if (grid->flag == 0)
		return (FLAG_BOTTOM);
	if (get_coord_value(grid->grid[y_zero + 1][x_zero], grid->x_y, &y, &x) <= 0)
		return (INT_MIN);
	ret1 = (y > y_zero) ? y - y_zero : y_zero - y;
	ret2 = (x > x_zero) ? x - x_zero : x_zero - x;
	ret = 0;
	if ((grid->flag & F_MANHATTAN) != 0)
		ret += ((grid->x_y - 1) * 2 - ret1 - ret2);
	if ((grid->flag & F_MAL_PLACE) != 0)
		ret += (ret1 + ret2 == 0 ? 1 : 0);
	return (ret);
}

int							get_weight_left(t_grid *grid, int const y_zero,
	int const x_zero)
{
	int						y, x, ret1, ret2, ret;

	if (grid == NULL || grid->grid == NULL || x_zero - 1 < 0)
		return (INT_MIN);
	if (grid->flag == 0)
		return (FLAG_LEFT);
	if (get_coord_value(grid->grid[y_zero][x_zero - 1], grid->x_y, &y, &x) <= 0)
		return (INT_MIN);
	ret1 = (y > y_zero) ? y - y_zero : y_zero - y;
	ret2 = (x > x_zero) ? x - x_zero : x_zero - x;
	ret = 0;
	if ((grid->flag & F_MANHATTAN) != 0)
		ret += ((grid->x_y - 1) * 2 - ret1 - ret2);
	if ((grid->flag & F_MAL_PLACE) != 0)
		ret += (ret1 + ret2 == 0 ? 1 : 0);
	return (ret);
}

int							get_weight_right(t_grid *grid, int const y_zero,
	int const x_zero)
{
	int						y, x, ret1, ret2, ret;

	if (grid == NULL || grid->grid == NULL || x_zero + 1 >= grid->x_y)
		return (INT_MIN);
	if (grid->flag == 0)
		return (FLAG_RIGHT);
	if (get_coord_value(grid->grid[y_zero][x_zero + 1], grid->x_y, &y, &x) <= 0)
		return (INT_MIN);
	ret1 = (y > y_zero) ? y - y_zero : y_zero - y;
	ret2 = (x > x_zero) ? x - x_zero : x_zero - x;
	ret = 0;
	if ((grid->flag & F_MANHATTAN) != 0)
		ret += ((grid->x_y - 1) * 2 - ret1 - ret2);
	if ((grid->flag & F_MAL_PLACE) != 0)
		ret += (ret1 + ret2 == 0 ? 1 : 0);
	return (ret);
}
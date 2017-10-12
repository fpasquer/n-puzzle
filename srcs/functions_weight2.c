/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_weight2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 08:57:47 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 10:03:08 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					general_weight(t_grid *grid, int const flag,
		int const y_zero, int const x_zero, int const y_new, int const x_new,
		int weight)
{
	int						y;
	int						x;
	int						ret;
	int						ret1;
	int						ret2;

	if ((ret = 0) == 0 && grid->flag == 0)
		return (flag);
	if (get_coord_value(grid->grid[y_new][x_new], grid->x_y, &y, &x) <= 0)
		return (INT_MIN);
	ret1 = (y > y_zero) ? y - y_zero : y_zero - y;
	ret2 = (x > x_zero) ? x - x_zero : x_zero - x;
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

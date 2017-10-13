/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_weight2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 08:57:47 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/13 09:54:51 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					general_weight(t_grid *grid, int const flag,
		t_coord const c_zero, t_coord const c_new, int weight)
{
	t_coord					c;
	int						ret;
	int						ret1;
	int						ret2;

	if ((ret = 0) == 0 && grid->flag == 0)
		return (rand() + flag);
	if (get_coord_value(grid->grid[c_new.y][c_new.x], grid->x_y, &c.y, &c.x)
			<= 0)
		return (INT_MIN);
	ret1 = (c.y > c_zero.y) ? c.y - c_zero.y : c_zero.y - c.y;
	ret2 = (c.x > c_zero.x) ? c.x - c_zero.x : c_zero.x - c.x;
	if ((grid->flag & F_MANHATTAN) != 0)
	{
		ret = weight + ret1 + ret2 + 10;
		ret -= (c.y > c_new.y) ? c.y - c_new.y : c_new.y - c.y;
		ret -= (c.x > c_new.x) ? c.x - c_new.x : c_new.x - c.x;
	}
	if ((grid->flag & F_MAL_PLACE) != 0)
		ret += (ret1 + ret2 == 0) ? 1 : 0;
	if ((grid->flag & F_LINEAR_C) != 0 && ret1 == 0 && c_zero.x < grid->x_y - 1)
		if (linear_conflict(grid, c_zero.y, c_zero.x, &ret) != true)
			return (INT_MIN);
	return (tile_out_r_c(grid, c_new, c, &ret));
}

int							get_weight_top(t_grid *grid, t_coord const c_zero,
		int weight)
{
	t_coord					cpy;

	if (grid == NULL || grid->grid == NULL || c_zero.y - 1 < 0)
		return (INT_MIN);
	cpy.y = c_zero.y - 1;
	cpy.x = c_zero.x;
	return (general_weight(grid, FLAG_TOP, c_zero, cpy, weight));
}

int							get_weight_bottom(t_grid *grid,
		t_coord const c_zero, int weight)
{
	t_coord					cpy;

	if (grid == NULL || grid->grid == NULL || c_zero.y + 1 >= grid->x_y)
		return (INT_MIN);
	cpy.y = c_zero.y + 1;
	cpy.x = c_zero.x;
	return (general_weight(grid, FLAG_BOTTOM, c_zero, cpy, weight));
}

int							get_weight_left(t_grid *grid, t_coord const c_zero,
		int weight)
{
	t_coord					cpy;

	if (grid == NULL || grid->grid == NULL || c_zero.x - 1 < 0)
		return (INT_MIN);
	cpy.y = c_zero.y;
	cpy.x = c_zero.x - 1;
	return (general_weight(grid, FLAG_LEFT, c_zero, cpy, weight));
}

int							get_weight_right(t_grid *grid, t_coord const c_zero,
		int weight)
{
	t_coord					cpy;

	if (grid == NULL || grid->grid == NULL || c_zero.x + 1 >= grid->x_y)
		return (INT_MIN);
	cpy.y = c_zero.y;
	cpy.x = c_zero.x + 1;
	return (general_weight(grid, FLAG_RIGHT, c_zero, cpy, weight));
}

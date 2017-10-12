/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heuristics.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 15:34:58 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 16:37:48 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

int							tile_out_r_c(t_grid *grid, t_coord const c_new,
		t_coord const coord, int *ret)
{
	if (grid == NULL || ret == NULL)
		return (INT_MIN);
	if ((grid->flag & F_TILE_OUT) == 0)
		return (*ret);
	*ret += 2;
	*ret -= c_new.y == coord.y ? 0 : 1;
	*ret -= c_new.x == coord.x ? 0 : 1;
	return (*ret);
}

bool						linear_conflict(t_grid *grid, int const y,
	int const x, int *weight)
{
	int						x_curs;
	int						y_dest;
	int						x_dest;

	if (grid == NULL || grid->grid == NULL || weight == NULL)
		return (false);
	x_curs = x + 1;
	while (x_curs < grid->x_y)
	{
		if (get_coord_value(grid->grid[y][x_curs], grid->x_y, &y_dest, &x_dest)
				<= 0)
			return (false);
		if (y_dest == y && x_dest <= x)
			(*weight) += 2;
		x_curs++;
	}
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doublon.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 08:12:55 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/13 08:13:30 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					count_val_grid(t_grid *grid, int const val)
{
	int						count;
	t_coord					coord;

	if (grid == NULL)
		return (-1);
	coord.y = 0;
	count = 0;
	while (coord.y < grid->x_y)
	{
		coord.x = 0;
		while (coord.x < grid->x_y)
			if (grid->grid[coord.y][coord.x++] == val)
				count++;
		coord.y++;
	}
	return (count);
}

t_grid						*check_grid_doublon(t_grid *grid)
{
	t_coord					c_val;

	if (grid == NULL)
		return (NULL);
	c_val.y = 0;
	while (c_val.y < grid->x_y)
	{
		c_val.x = 0;
		while (c_val.x < grid->x_y)
		{
			if (count_val_grid(grid, grid->grid[c_val.y][c_val.x]) != 1)
			{
				ft_memdel((void**)&grid);
				return (NULL);
			}
			c_val.x++;
		}
		c_val.y++;
	}
	return (grid);
}

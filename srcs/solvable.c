/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 09:10:59 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/11 12:27:19 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					find_value_position(int const grid[], int const x_y,
		int const value)
{
	int						i;
	int						end;

	for (i = 0, end = x_y * x_y; i < end; i++)
		if (grid[i] == value)
			return (i);
	return (-1);
}

static int					find_value_dest(int const x_y, int value)
{
	int						end;
	int						i;

	end = x_y * x_y;
	if (value == EMPTY)
		return (end - 1);
	for (i = 0, value--; i < end; i++)
		if (i == value)
			return (i);
	return (-1);
}

static bool					solvable_check(int grid[], int const x_y,
		int const end)
{
	int						i;
	int						position;
	int						dest;
	int						switch_val;
	int						tmp;

	for (i = 0, switch_val = 0; i < end; ++i)
	{

		if ((position = find_value_position(grid, x_y, i)) == -1)
			return (false);
		if ((dest = find_value_dest(x_y, i)) == -1)
			return (false);
		if (position != dest)
		{
			tmp = grid[position];
			grid[position] = grid[dest];
			grid[dest] = tmp;
			switch_val++;
		}
	}
	return (switch_val % 2);
}

bool						solvable(t_grid *grid)
{
	bool					ret;
	int						y;
	int						x;
	int						i;
	int						*grid_tab;

	if (grid == NULL || grid->grid == NULL)
		return (false);
	if ((grid_tab = ft_memalloc(sizeof(int) * (grid->x_y * grid->x_y))) == NULL)
		return (false);
	for (y = 0, i = 0; y < grid->x_y; y++)
		for (x = 0; x < grid->x_y; x++, i++)
			grid_tab[i] = grid->grid[y][x];
	ret = solvable_check(grid_tab, grid->x_y, grid->x_y * grid->x_y);
	ft_memdel((void**)&grid_tab);
	grid->found = ret == false ? true : grid->found;
	printf("La grille est %s\n", ret == true ? "Solvable" : "Insolvable");
	return (ret);
}
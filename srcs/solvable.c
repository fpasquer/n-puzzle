/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 09:10:59 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/10 19:23:42 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					find_value_position(int const grid[], int const x_y,
		int const value)
{
	int						i;
	int						end;

	i = 0;
	end = x_y * x_y;
	while (i < end)
		if (grid[i++] == value)
			return (i - 1);
	return (-1);
}

static int					find_value_dest(int const x_y, int value)
{
	int						end;
	int						i;

	end = x_y * x_y;
	if (value == EMPTY)
		return (end - 1);
	i = 0;
	value--;
	while (i < end)
		if (i++ == value)
			return (i - 1);
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

	i = 0;
	switch_val = 0;
	while (i < end)
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
		i++;
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
	i = 0;
	y = 0;
	while (y < grid->x_y)
	{
		x = 0;
		while (x < grid->x_y)
			grid_tab[i++] = grid->grid[y][x++];
		y++;
	}
	ret = solvable_check(grid_tab, grid->x_y, grid->x_y * grid->x_y);
	ft_memdel((void**)&grid_tab);
	grid->found = ret == false ? true : grid->found;
	printf("La grille est %s\n", ret == true ? "Solvable" : "Insolvable");
	return (ret);
}

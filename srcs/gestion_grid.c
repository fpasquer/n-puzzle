/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 08:37:18 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/20 11:27:38 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

# define COOF_DEEP 3

static bool					get_grid_loop(t_grid *grid, char **file, int *j,
		int const k, int const y, int const x)
{
	if (grid == NULL || file == NULL || j == NULL)
		return (false);
	while (file[k][*j] == ' ')
		(*j)++;
	grid->grid[y][x] = (int)ft_atoi(&file[k][*j]);
	while (ft_isdigit(file[k][*j]) == true)
		(*j)++;
	while (file[k][*j] == ' ')
		(*j)++;
	return (true);
}

t_grid						*get_grid(char **file, int const x_y,
		int const flags)
{
	int						x, y, j, k;
	t_grid					*grid;

	if (file == NULL || (grid = ft_memalloc(sizeof(*grid))) == NULL)
		return (NULL);
	if ((grid->grid = ft_memalloc(sizeof(int*) * x_y)) == NULL)
		return (NULL);
	for(k = 0; file[k][0] == '#'; k++);
	if (ft_is_number(file[k++]) == 0)
		return (NULL);
	for (y = 0; y < x_y; y++)
		if ((grid->grid[y] = ft_memalloc(sizeof(int) * x_y)) == NULL)
			return (NULL);
	for (grid->x_y = x_y, y = 0; y < grid->x_y; y++, k++)
		for (x = 0, j = 0; x < grid->x_y && file[k] != NULL; x++)
			if (get_grid_loop(grid, file, &j, k, y, x) == false)
				return (NULL);
	grid->prev.y = grid->prev.x = -1;
	ft_bzero(g_way_good, sizeof(g_way_good));
	grid->max_deep = get_weight_init(grid);
	grid->flag = flags;
	grid->end = grid->x_y * grid->x_y - 1;
	return (grid);
}

bool						del_grid(t_grid **grid)
{
	int						y;

	if (grid == NULL || *grid == NULL || (*grid)->grid == NULL)
		return (false);
	y = 0;
	while (y < (*grid)->x_y)
		ft_memdel((void**)&(*grid)->grid[y++]);
	ft_memdel((void**)&(*grid)->grid);
	ft_memdel((void**)grid);
	return (true);
}
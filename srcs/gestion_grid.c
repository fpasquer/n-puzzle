/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 08:37:18 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 08:22:23 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

#define COOF_DEEP 3

static bool					get_grid_loop(t_grid *grid, char **file, int *j,
		int const k, int const y, int const x)
{
	if (grid == NULL || file == NULL || *file == NULL || j == NULL)
		return (false);
	while (file[k][*j] == ' ')
		(*j)++;
	grid->grid[y][x] = (int)ft_atoi(&file[k][*j]);
	while (ft_isdigit(file[k][*j]) == true)
		(*j)++;
	while (file[k][*j] == ' ')
		(*j)++;
	if (file[k][*j] == '#')
		while (file[k][*j] != '\0')
			(*j)++;
	return (true);
}

static bool					start_get_grid_loop(t_grid **grid, char **file,
		int k)
{
	int						y;
	int						x;
	int						j;

	if (grid == NULL || file == NULL || *file == NULL || k < 0)
		return (false);
	y = 0;
	while (file[k] != NULL)
	{
		x = 0;
		j = 0;
		while (x < (*grid)->x_y)
			if (get_grid_loop(*grid, file, &j, k, y, x++) == false)
				return (false);
		k++;
		skip_comment(file, &k);
		y++;
	}
	return (true);
}

static t_grid				*start_get_grid(t_grid *grid, int const flags,
		char **file)
{
	int						k;

	if (grid == NULL || grid->grid == NULL)
		return (NULL);
	k = 0;
	skip_comment(file, &k);
	if (ft_atoi(file[k++]) == 0)
		return (NULL);
	skip_comment(file, &k);
	if (start_get_grid_loop(&grid, file, k) == false)
		return (NULL);
	grid->prev.y = -1;
	grid->prev.x = -1;
	ft_bzero(g_way_good, sizeof(g_way_good));
	grid->max_deep = get_weight_init(grid);
	grid->flag = flags;
	grid->end = grid->x_y * grid->x_y - 1;
	return (grid);
}

t_grid						*get_grid(char **file, int const x_y,
		int const flags)
{
	int						y;
	t_grid					*grid;

	if (file == NULL || (grid = ft_memalloc(sizeof(*grid))) == NULL)
		return (NULL);
	if ((grid->grid = ft_memalloc(sizeof(int*) * x_y)) == NULL)
		return (NULL);
	y = 0;
	while (y < x_y)
		if ((grid->grid[y++] = ft_memalloc(sizeof(int) * x_y)) == NULL)
			return (NULL);
	grid->x_y = x_y;
	return (start_get_grid(grid, flags, file));
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:26:06 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/11 14:29:01 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static void					need_argv(void)
{
	ft_putstr_fd("Need file", STDOUT_FILENO);
	exit(EXIT_FAILURE);
}

void						start_loop(t_grid *grid, t_coord coord_zero,
		char **file, int fd)
{
	clock_t					start;

	if (grid == NULL || grid->grid == NULL || file == NULL || fd <= 1)
		return ;
#ifdef DEBUG
	printf("weight = %d\n", get_weight_init(grid));
	printf("max_deep = %d\n", grid->max_deep);
	grid->max_deep = 1;
#endif
	for (start = clock(); grid->max_deep < MAX_DEEP &&
			grid->found == false; grid->max_deep++)
		solve_npuzzle(grid, 0, coord_zero.y, coord_zero.x,
			get_move_possible(grid, coord_zero.y, coord_zero.x), is_Done(grid));
	printf("Time = %f\nMemory = %zu octets\n", (double)(clock() - start) / CLOCKS_PER_SEC, sizeof(*grid) * grid->max_deep);
	show_way(grid, &file, fd, coord_zero.y, coord_zero.x);
}

int							main(int argc, char **argv)
{
	char					**file;
	int						x_y, fd, flags;
	t_coord					coord_zero;
	t_grid					*grid;

	flags = 0;
	if (argc <= 1)
		need_argv();
	if ((fd = check_argv(argv, &flags)) > 1)
	{
#ifdef DEBUG
		printf("flags = %d\n", flags);
#endif
		if ((file = save_file(fd)) != NULL)
		{
			if ((x_y = check_file(file)) > 0)
				if ((grid = get_grid(file, x_y, flags)) != NULL &&
						get_coord_zero(grid, &coord_zero) == true)
					if (solvable(grid) == true)
						start_loop(grid, coord_zero, file, fd);
			del_file(&file);
		}
		close(fd);
	}
	ft_putstr_fd("Error\n", STDERR_FILENO);
	return (EXIT_SUCCESS);
}
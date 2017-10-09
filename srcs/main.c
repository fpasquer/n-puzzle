/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:26:06 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/20 11:26:50 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

bool						print_flag(unsigned int const flag)
{
	char					non[] = "\033[31mNon\033[0m";
	char					oui[] = "\033[32mOui\033[0m";

	printf("Manhattan       %s\n", (flag & F_MANHATTAN) == 0 ? non : oui);
	printf("Linear conflict %s\n", (flag & F_LINEAR_C) == 0 ? non : oui);
	printf("Wrong place     %s\n", (flag & F_MAL_PLACE) == 0 ? non : oui);
	return (true);
}

void						start_loop(t_grid *grid, t_coord coord_zero,
		char **file, int fd)
{
	int						right_coord;
	int						weight;
	clock_t					start;

	if (grid == NULL || grid->grid == NULL || file == NULL || fd <= 1)
		return ;
	get_coord_value(0, grid->x_y, &right_coord, &weight);
	right_coord = is_Done(grid);
	weight = grid->max_deep;
	printf("weight manhattan + linear_conflict = %d\n", weight);
	for (start = clock(); grid->max_deep < MAX_DEEP &&
			grid->found == false; grid->max_deep++)
		solve_npuzzle(grid, 0, coord_zero.y, coord_zero.x,
				get_move_possible(grid, coord_zero.y, coord_zero.x),
				right_coord, weight);
	printf("Time = %f\nMemory = %zu octets\n", (double)(clock() - start) /
			CLOCKS_PER_SEC, sizeof(*grid) * grid->max_deep);
	show_way(grid, &file, fd, coord_zero.y, coord_zero.x);
}

int							main(int argc, char **argv)
{
	char					**file;
	int						x_y, fd, flags;
	t_coord					coord_zero;
	t_grid					*grid;

	flags = 0;
	if (argc <= 1 && generate_grid() == false)
	{
		ft_putstr_fd("Error file\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if ((fd = check_argv(argv, &flags)) > 1 && print_flag(flags) == true)
	{
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
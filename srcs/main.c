/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:26:06 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/13 11:02:20 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

bool						print_flag(unsigned int const flag)
{
	printf("Random          %s\n", flag != 0 ? "\033[31mNon\033[0m" :
			"\033[32mOui\033[0m");
	printf("Manhattan       %s\n", (flag & F_MANHATTAN) == 0 ?
			"\033[31mNon\033[0m" : "\033[32mOui\033[0m");
	printf("Linear conflict %s\n", (flag & F_LINEAR_C) == 0 ?
			"\033[31mNon\033[0m" : "\033[32mOui\033[0m");
	printf("Wrong place     %s\n", (flag & F_MAL_PLACE) == 0 ?
			"\033[31mNon\033[0m" : "\033[32mOui\033[0m");
	printf("Tile_out        %s\n", (flag & F_TILE_OUT) == 0 ?
			"\033[31mNon\033[0m" : "\033[32mOui\033[0m");
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
	right_coord = is_done(grid);
	weight = grid->max_deep;
	printf("weight manhattan + linear_conflict = %d\n", weight);
	start = clock();
	while (grid->max_deep < MAX_DEEP && grid->found == false)
	{
		solve_npuzzle(grid, 0, coord_zero,
				get_move_possible(grid, coord_zero),
				right_coord, weight);
		grid->max_deep++;
	}
	printf("Time = %f\nMemory = %zu octets\n", (double)(clock() - start) /
			CLOCKS_PER_SEC, sizeof(*grid) * grid->max_deep);
	show_way(grid, &file, fd, coord_zero);
	exit(EXIT_SUCCESS);
}

static void					main_next(int const fd, int const flags)
{
	char					**file;
	int						x_y;
	t_grid					*grid;
	t_coord					coord_zero;

	if (fd <= 0)
		return ;
	if ((file = save_file(fd)) != NULL)
	{
		if ((x_y = check_file(file)) > 0)
			if ((grid = get_grid(file, x_y, flags)) != NULL &&
					get_coord_zero(grid, &coord_zero) == true)
				if (solvable(grid) == true)
					start_loop(grid, coord_zero, file, fd);
		del_file(&file);
	}
}

int							main(int argc, char **argv)
{
	int						fd;
	int						flags;

	flags = 0;
	srand(getpid());

	if (argc <= 1 && generate_grid() == false)
	{
		ft_putstr_fd("Error file\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if ((fd = check_argv(argv, &flags)) > 1 && print_flag(flags) == true)
	{
		main_next(fd, flags);
		close(fd);
	}
	ft_putstr_fd("Error\n", STDERR_FILENO);
	return (EXIT_SUCCESS);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   npuzzle.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:27:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/20 10:57:32 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NPUZZLE_H
# define NPUZZLE_H

# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/mman.h>
#include "../minilibx_macos/mlx.h"
#include <time.h>

# define NB_PIX_EACH_BOX 100

# define STEEP_DEEP 5

# define DEFAULT_SIZE 3u
# define DEFAULT_FILE "grid"

//# define DEBUG

#ifdef DEBUG
	# define MAX_DEEP 5
#else
	# define MAX_DEEP 50
#endif
# define MAX_WAY 4

# define SIZE_file_MIN 3
# define SIZE_file_MAX 5

# define EMPTY 0

# define MOVE_TOP 0
# define MOVE_BOTTOM 1
# define MOVE_LEFT 2
# define MOVE_RIGHT 3
# define NO_MOVE 4

# define FLAG_NONE 0x0
# define FLAG_TOP 0x1
# define FLAG_BOTTOM 0x2
# define FLAG_LEFT 0x4
# define FLAG_RIGHT 0x8

# define F_MANHATTAN 0x1
# define F_MAL_PLACE 0x2
# define F_LINEAR_C 0x4

//int							g_way_move[MAX_DEEP];
int							g_way_good[MAX_DEEP];
int							g_grid_3x3[3][3];
int							g_grid_4x4[4][4];
int							g_grid_5x5[5][5];

typedef struct				s_coord
{
	int						x;
	int						y;
}							t_coord;

typedef struct				s_grid
{
	bool					found;
	int						end;
	int						max_deep;
	int						x_y;
	int						**grid;
	int						flag;
	t_coord					prev;
}							t_grid;

typedef struct				s_way_weight
{
	int						index;
	int						way;
	int						weight;
}							t_way_weight;

typedef struct				s_mlx_npuzzle
{
	void					*mlx;
	void					*win;
	void					**img;
	char					***file;
	int						x_zero;
	int						y_zero;
	int						fd;
	int						t[3];
	int						**data;
	t_grid					*grid;
	clock_t					time;
}							t_mlx_npuzzle;

typedef struct				s_func_move
{
	int						key;
	int						(*f)(t_grid *, int, int const, int const, int const,
			int, int);
}							t_func_move;

typedef struct				s_func_weight
{
	int						key;
	int						(*f)(t_grid *, int const, int const, int);
}							t_func_weight;

typedef struct				s_func_move_show
{
	int						key;
	int						(*f)(t_mlx_npuzzle **);
}							t_func_move_show;

int							check_argv(char **path, int *flags);
char						**save_file(int const fd);
int							check_file(char **file);
bool						print_file(char **file);
bool						del_file(char ***file);
t_grid						*get_grid(char **file, int const x_y, int const flags);
bool						print_grid(t_grid *grid, int const deep,
		unsigned int move);
bool						del_grid(t_grid **grid);
void						solve_npuzzle(t_grid *grid, int loop,
		int const x_zero, int const y_zero, int const move, int right_coord,
		int weight);
bool						get_coord_zero(t_grid *grid, t_coord *coord);
int							get_move_possible(t_grid *grid, int const y_zero,
		int const x_zero);
int							is_Done(t_grid *grid);

int							move_top(t_grid *grid, int loop,
		int const y_zero, int const x_zero, int const move, int right_coord,
		int weight);
int							move_bottom(t_grid *grid, int loop,
		int const y_zero, int const x_zero, int const move, int right_coord,
		int weight);
int							move_left(t_grid *left, int loop, int const y_zero,
		int const x_zero, int const move, int right_coord, int weight);
int							move_right(t_grid *right, int loop,
		int const y_zero, int const x_zero, int const move, int right_coord,
		int weight);

int							show_move_top(t_mlx_npuzzle **mlx);
int							show_move_bottom(t_mlx_npuzzle **mlx);
int							show_move_left(t_mlx_npuzzle **mlx);
int							show_move_right(t_mlx_npuzzle **mlx);

void						show_way(t_grid *grid, char ***file, int fd,
		int const y_zero, int const x_zero);
int							draw_grid(t_mlx_npuzzle *mlx);
int							key_hook(int key, void *param);
int							loop_hook(void *param);
int							close_hook(int button, void *param);
void						leave_window(t_mlx_npuzzle **mlx);

int							get_order_ways(t_grid *grid,
		t_way_weight ways[MAX_DEEP], int const move, int const y_zero,
		int const x_zero, int weight);
int							get_weight_top(t_grid *grid, int const y_zero,
		int const x_zero, int weight);
int							get_weight_bottom(t_grid *grid, int const y_zero,
		int const x_zero, int weight);
int							get_weight_left(t_grid *grid, int const y_zero,
		int const x_zero, int weight);
int							get_weight_right(t_grid *grid, int const y_zero,
		int const x_zero, int weight);
int							get_weight_init(t_grid *grid);

bool						solvable(t_grid *grid);
int							get_coord_value(int value, int const x_y, int *y,
		int *x);
bool						generate_grid(void);

#endif
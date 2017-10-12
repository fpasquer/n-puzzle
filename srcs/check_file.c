/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 10:50:30 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 15:22:04 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

int							skip_comment(char **file, int *y)
{
	if (y == NULL || file == NULL || *file == NULL || (*y) < 0)
		return (false);
	while (file[(*y)] != NULL && file[(*y)][0] == '#')
		(*y)++;
	return (true);
}

static int					loop_check_file2(char **file, t_coord *coord,
		int const max_num, int const ret)
{
	int						nb_number;
	int						num;

	if (file == NULL || *file == NULL || coord == NULL)
		return (false);
	if (file[coord->y] == NULL)
		return (ret);
	nb_number = 0;
	while (file[coord->y][coord->x] != '\0')
	{
		while (file[coord->y][coord->x] == ' ')
			coord->x++;
		if (ft_isdigit(file[coord->y][coord->x]) != true ||
				(num = ft_atoi(&file[coord->y][coord->x])) < 0 || num > max_num)
			return (false);
		while (ft_isdigit(file[coord->y][coord->x]) == true)
			coord->x++;
		while (file[coord->y][coord->x] == ' ')
			coord->x++;
		nb_number++;
		if (file[coord->y][coord->x] == '#')
			while (file[coord->y][coord->x] != '\0')
				coord->x++;
	}
	return (nb_number);
}

static int					loop_check_file(char **file, int y, int num)
{
	int						nb_number;
	int						ret;
	int						max_f_num;
	t_coord					coord;

	if (file == NULL || *file == NULL || y < 0)
		return (false);
	ret = num;
	max_f_num = num * num - 1;
	coord.y = y;
	while (file[coord.y] != NULL)
	{
		nb_number = 0;
		coord.x = 0;
		if ((nb_number = loop_check_file2(file, &coord, max_f_num, ret)) == -1)
			return (false);
		if (nb_number != ret)
			return (false);
		coord.y++;
		skip_comment(file, &coord.y);
	}
	return (ret);
}

int							check_file(char **file)
{
	int						y;
	int						num;

	y = 0;
	if (file == NULL || *file == NULL || skip_comment(file, &y) == false)
		return (false);
	if (file[y] == NULL || (num = ft_atoi(file[y])) < SIZE_FILE_MIN ||
			num > SIZE_FILE_MAX)
		return (false);
	y++;
	skip_comment(file, &y);
	return (file[y] == NULL ? false : loop_check_file(file, y, num));
}

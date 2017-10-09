/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 18:10:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/20 11:27:53 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

char						**save_file(int const fd)
{
	char					*file_content;
	char					**file;
	off_t					size_file;

	if (fd <= 0 || (size_file = lseek(fd, 0, SEEK_END)) <= 0)
		return (NULL);
	if ((file_content = mmap(NULL, size_file, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (NULL);
	file = ft_strsplit(file_content, '\n');
	munmap(file_content, size_file);
	return (file);
}

int							check_file(char **file)
{
	int						y, x, num, ret, nb_number;

	if (file == NULL || *file == NULL)
		return (false);
	for (num = 0, y = 0; file[y] != NULL && file[y][0] == '#'; y++);
	if (file[y] == NULL || (ret = num = ft_atoi(file[y])) < SIZE_file_MIN)
		return (false);
	for (int max_f_num = num * num - 1; file[++y] != NULL;)
	{
		for (nb_number = 0, x = 0; file[y][x] != '\0'; nb_number++)
		{
			while (file[y][x] == ' ')
				x++;
			if (ft_isdigit(file[y][x]) != true ||
					(num = ft_atoi(&file[y][x])) < 0 || num > max_f_num)
				return (false);
			while (ft_isdigit(file[y][x]) == true)
				x++;
			while (file[y][x] == ' ')
				x++;
		}
		if (nb_number != ret)
			return (false);
	}
	return (ret);
}

bool						print_file(char **file)
{
	unsigned int			y;

	if (file == NULL || *file == NULL)
		return (false);
	y = 0;
	while (file[y] != NULL)
		ft_putendl(file[y++]);
	return (true);
}

bool						del_file(char ***file)
{
	unsigned int			y;
	
	if (file == NULL || *file == NULL || **file == NULL)
		return (false);
	y = 0;
	ft_free_strsplit(*file);
	return (true);
}
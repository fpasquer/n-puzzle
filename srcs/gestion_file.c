/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 18:10:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 08:21:14 by fpasquer         ###   ########.fr       */
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

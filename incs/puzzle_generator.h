/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_generator.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:47:55 by amaindro          #+#    #+#             */
/*   Updated: 2017/10/12 14:00:11 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUZZLE_GENERATOR_H
# define PUZZLE_GENERATOR_H

# include "../libft/libft.h"
# include <time.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdio.h>

int		*make_solvable_or_not(int size, int solvable, int *puzzle);
int		*puzzle_swapper(int s, int *puzzle);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 15:55:24 by mgama             #+#    #+#             */
/*   Updated: 2024/01/12 16:11:30 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_STRUCTS_H
# define MATH_STRUCTS_H

typedef struct s_pointi2
{
	int			x;
	int			y;
}				t_pointi2;

typedef struct s_pointf2
{
	float		x;
	float		y;
}				t_pointf2;

typedef struct s_screen_dim
{
	int			top;
	int			left;
	int			width;
	int			height;
	int			center_x;
	int			center_y;
}				t_screen_dim;

typedef struct s_fmat2
{
	float		_00;
	float		_01;
	float		_10;
	float		_11;
}				t_fmat2;

#endif /* MATH_STRUCTS_H */
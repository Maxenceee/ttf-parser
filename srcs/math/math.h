/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:56:17 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 11:56:03 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_H
# define MATH_H

# include <math.h>
# include "math_structs.h"

/* points */

t_pointf2		ft_create_fpoint(float x, float y);
t_pointi2		ft_dims_to_ipoint(t_screen_dim dims);
t_pointi2		ft_create_ipoint(int x, int y);
t_pointi2		*ft_copy_ipoint(t_pointi2 point);
t_pointf2		*ft_copy_fpoint(t_pointf2 point);

/* dist */

float			ft_dist_btw_pointsf(t_pointf2 p1, t_pointf2 p2);
float			ft_dist_btw_points(t_pointi2 p1, t_pointi2 p2);

/* angles */

float			ft_deg_to_rad(float angle);
float			ft_rad_to_deg(float angle);
float			ft_normalize_angle(double angle);

/* scredims */

t_screen_dim	ft_create_dims(int left, int top, int w, int h);
t_screen_dim	*ft_copy_dims(t_screen_dim dims);
void			ft_print_sdims(t_screen_dim d);

#endif /* MATH_H */
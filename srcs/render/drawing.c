/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:02:02 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"
#include "math/math.h"
#include "images/images.h"

void	ft_quadratic_bezier(t_img *image, t_pointi2	start, t_pointi2 control, t_pointi2 end, uint16_t steps, uint32_t color)
{
	float	t;
	int		x;
	int		y;
	int		i;

	i = 0;
	while (i <= steps)
	{
		t = (float)i / steps;
		x = (1 - t) * (1 - t) * start.x + 2 * (1 - t)
			* t * control.x + t * t * end.x;
		y = (1 - t) * (1 - t) * start.y + 2 * (1 - t)
			* t * control.y + t * t * end.y;
		ft_pixel_put(image, x, y, color);
		i++;
	}
}

void	ft_draw_line(t_img *image, t_pointi2 p1, t_pointi2 p2, uint32_t c)
{
	float	t;
	float	gap;

	t = 0.f;
	gap = 0.001f;
	while (t < 1.f)
	{
		ft_pixel_put(image, p1.x + t * (p2.x - p1.x),
			p1.y + t * (p2.y - p1.y), c);
		t += gap;
	}
}

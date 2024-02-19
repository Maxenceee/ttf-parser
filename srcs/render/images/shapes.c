/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.C                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 13:43:43 by mgama             #+#    #+#             */
/*   Updated: 2024/02/19 14:23:23 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"

void	ft_draw_rect(t_screen_dim s_dims, t_img *image, uint32_t color)
{
	int		y;
	int		x;

	y = -1;
	while (++y < s_dims.height)
	{
		x = -1;
		while (++x < s_dims.width)
		{
			ft_pixel_put(image,
				s_dims.left + x,
				s_dims.top + y,
				color);
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_pixel.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 16:55:38 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 12:30:35 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"

uint32_t	ft_get_pixel(t_img *img, int x, int y)
{
	int		addr_index;
	int		*color;

	addr_index = (y * img->line_length + x * img->bits_per_pixel);
	if (addr_index >= 0 && addr_index < img->max_addr)
	{
		color = (int *)(img->addr + addr_index);
		return (*color);
	}
	return (-1);
}

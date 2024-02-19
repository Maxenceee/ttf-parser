/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:06:57 by mgama             #+#    #+#             */
/*   Updated: 2024/02/19 14:23:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"

void	ft_pixel_put(t_img *img, int x, int y, uint32_t color)
{
	int	*dst;
	int	addr;

	dst = (int *)img->addr;
	addr = y * (img->line_length >> 2) + x;
	if (addr >= 0 && addr < img->max_addr)
		dst[addr] = color;
}

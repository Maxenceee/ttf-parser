/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pixel_put.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:06:57 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 12:35:34 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, uint32_t color)
{
	int	*dst;
	int	addr;

	dst = (int *)img->addr;
	addr = y * (img->line_length >> 2) + x;
	if (addr >= 0 && addr < img->max_addr)
		dst[addr] = color;
}

void	ft_pixel_put_to_image(t_img *image, int x, int y, uint32_t color)
{
	char	*dst;
	int		pixel;

	pixel = y * image->line_length + x * image->bits_per_pixel;
	if (pixel > image->size)
		return ;
	dst = image->addr + pixel;
	*(uint32_t *)dst = color;
}

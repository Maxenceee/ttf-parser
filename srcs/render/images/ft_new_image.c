/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 20:03:10 by rbonneva          #+#    #+#             */
/*   Updated: 2024/02/18 12:34:49 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"

t_img	*ft_new_image(void *mlx_ptr, int width, int height)
{
	void	*img_ptr;
	t_img	*new_image;

	img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (img_ptr == NULL)
		return (NULL);
	new_image = calloc(1, sizeof(t_img));
	if (new_image == NULL)
		return (mlx_destroy_image(mlx_ptr, img_ptr), NULL);
	new_image->img = img_ptr;
	new_image->addr = mlx_get_data_addr(new_image->img, \
										&(new_image->bits_per_pixel), \
										&(new_image->line_length), \
										&(new_image->endian));
	if (new_image->addr == NULL)
		return (mlx_destroy_image(mlx_ptr, img_ptr), free(new_image), NULL);
	new_image->max_addr = new_image->line_length * height;
	new_image->bits_per_pixel /= 8;
	new_image->size = (width * height * new_image->bits_per_pixel);
	new_image->width = width;
	new_image->height = height;
	return (new_image);
}

void	ft_delete_image(void *mlx_ptr, t_img **image)
{
	mlx_destroy_image(mlx_ptr, (*image)->img);
	free(*image);
	*image = NULL;
}

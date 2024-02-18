/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_image_to_window.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:50:06 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 12:30:37 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "images.h"

int	ft_put_image_to_window(t_data *mlx, t_img *image, int x, int y)
{
	return (mlx_put_image_to_window(mlx->mlx, mlx->window, image->img, x, y));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_sdims.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:10:34 by mgama             #+#    #+#             */
/*   Updated: 2024/02/18 11:35:30 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

t_screen_dim	*ft_copy_dims(t_screen_dim dims)
{
	t_screen_dim	*sdims;

	sdims = (t_screen_dim *)ft_calloc(1, sizeof(t_screen_dim));
	if (!sdims)
		return (NULL);
	sdims->left = dims.left;
	sdims->top = dims.top;
	sdims->width = dims.width;
	sdims->height = dims.height;
	sdims->center_x = dims.center_x;
	sdims->center_y = dims.center_y;
	return (sdims);
}

t_screen_dim	ft_create_dims(int left, int top, int w, int h)
{
	int	center_x;
	int	center_y;

	center_x = w >> 1;
	center_y = h >> 1;
	return ((t_screen_dim){
		.left = left, .top = top,
		.width = w, .height = h,
		.center_x = center_x, .center_y = center_y});
}

void	ft_print_sdims(t_screen_dim d)
{
	printf("left=%d top=%d w=%d h=%d cx=%d cy=%d\n",
		d.left, d.top, d.width, d.height, d.center_x, d.center_y);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:18:34 by rbonneva          #+#    #+#             */
/*   Updated: 2024/02/19 14:49:00 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_H
# define IMAGES_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>

#include "math/math.h"

typedef struct s_img	t_img;

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			max_addr;
	int			bits_per_pixel;
	int			line_length;
	int			size;
	int			endian;
	int			width;
	int			height;
}				t_img;

#define TRANSP_BYTE	0xFF << 24

/* mlx defines */

void	*mlx_new_image(void *,int,int);
int		mlx_destroy_image(void *,void *);
char	*mlx_get_data_addr(void *,int *,int *,int *);

/* mlx_pixel_put */

void		ft_pixel_put(t_img *img, int x, int y, uint32_t color);

/* mlx_new_image */

t_img		*ft_new_image(void *mlx_ptr, int width, int height);
void		ft_delete_image(void *mlx_ptr, t_img **image);

/* get pixel */

uint32_t	ft_get_pixel(t_img *img, int x, int y);

/* drawing */

void		ft_draw_rect(t_screen_dim s_dims, t_img *image, uint32_t color);

#endif /* IMAGES_H */

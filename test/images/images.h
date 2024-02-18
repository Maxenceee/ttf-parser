/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:18:34 by rbonneva          #+#    #+#             */
/*   Updated: 2024/02/18 12:35:48 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGES_H
# define IMAGES_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <fcntl.h>

# ifdef __APPLE__
#  include "../libmlx_mac/mlx.h"
# else
#  include "../.libmlx_linux/mlx.h"
# endif /* __APPLE__ */

typedef struct s_data			t_data;
typedef struct s_img			t_img;

typedef struct s_data
{
	void			*mlx;
	void			*window;
	t_img			*image;
}			t_data;

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

/* mlx_pixel_put */

void	ft_mlx_pixel_put(t_img *img, int x, int y, uint32_t color);
void	ft_pixel_put_to_image(t_img *image, int x, int y, uint32_t color);

/* mlx_new_image */

t_img	*ft_new_image(void *mlx_ptr, int width, int height);
void	ft_delete_image(void *mlx_ptr, t_img **image);

/* get pixel */

int		ft_get_pixel_from_img(t_img *img, int x, int y);

/* put image to window */

int		ft_put_image_to_window(t_data *mlx, t_img *image, int x, int y);

#endif /* IMAGES_H */

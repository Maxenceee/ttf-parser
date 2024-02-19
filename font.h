/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 14:08:25 by mgama             #+#    #+#             */
/*   Updated: 2024/02/19 14:33:02 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FONT_H
#define FONT_H

# include <stdint.h>

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

int		ft_create_new_font(const char *type, char *path, const char *font_name);
int		ft_delete_font(const char *font_name);

t_img	*ft_create_string(void *mlx, void *image, const char *text,
			uint32_t size, uint32_t color, const char *font_name, int *width, int *height);

/* images */

t_img		*ft_new_image(void *, int, int);
void		ft_delete_image(void *, t_img **);
void		ft_pixel_put(t_img *, int, int, uint32_t);
uint32_t	ft_get_pixel(t_img *, int, int);

#endif /* FONT_H */